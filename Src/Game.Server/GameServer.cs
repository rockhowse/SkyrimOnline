using Lidgren.Network;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Game.API.Managers;
using Game.API.Entities;
using Game.API.Networking;
using Game.API.Networking.Messages;
using Microsoft.Xna.Framework;
using Game.Server.World;
using log4net;
using System.Reflection;

namespace Game.Server
{
    public class GameServer
    {
        private static readonly ILog Logger = LogManager.GetLogger(MethodBase.GetCurrentMethod().DeclaringType);

        private NetServer server;
        private GameTime appTime;
        private GameWorld world;
        private Dictionary<NetConnection, Session> sessions = new Dictionary<NetConnection, Session>();

        public GameServer(string pName, int port)
        {
            Name = pName;
            world = new GameWorld(this);

            NetPeerConfiguration config = new NetPeerConfiguration("game");
            config.EnableMessageType(NetIncomingMessageType.ConnectionApproval);
            config.EnableMessageType(NetIncomingMessageType.StatusChanged);
            config.EnableMessageType(NetIncomingMessageType.Data);
            config.Port = port;

            server = new NetServer(config);
            server.Start();

            this.Initialize();

            Logger.InfoFormat("Started {0} on port {1} !", Name, port);

        }

        protected void Initialize()
        {
            appTime = new GameTime();


            // this.playerManager.PlayerStateChanged += (sender, e) => this.SendMessage(new UpdatePlayerStateMessage(e.Player));
        }

        public void SendMessage(IGameMessage gameMessage)
        {
            try
            {
                foreach (var s in sessions)
                {
                    s.Value.SendMessage(gameMessage);
                }
            }
            catch (System.Exception ex)
            {
                Logger.Error(ex.ToString());
            }
        }

        public void Update()
        {
            try
            {

                ProcessNetworkMessages();

                this.world.Update(this.appTime);
            }
            catch (System.Exception ex)
            {
                Logger.Error(ex.ToString());
            }
        }

        private void ProcessNetworkMessages()
        {
            NetIncomingMessage inc;
            while ((inc = server.ReadMessage()) != null)
            {
                switch (inc.MessageType)
                {
                    case NetIncomingMessageType.StatusChanged:
                        NetConnectionStatus status = (NetConnectionStatus)inc.ReadByte();
                        switch (status)
                        {
                            case NetConnectionStatus.Connected:
                                Logger.InfoFormat("{0} Connected", inc.SenderEndpoint);
                                break;
                            case NetConnectionStatus.Disconnected:
                                sessions.Remove(inc.SenderConnection);
                                Logger.InfoFormat("{0} Disconnected", inc.SenderEndpoint);
                                break;
                            case NetConnectionStatus.Disconnecting:
                            case NetConnectionStatus.InitiatedConnect:
                            case NetConnectionStatus.RespondedConnect:
                                Logger.Debug(status.ToString());
                                break;
                        }
                        break;
                    //Check for client attempting to connect
                    case NetIncomingMessageType.ConnectionApproval:

                        NetOutgoingMessage hailMessage;
                        if (world.EnterWorld(inc, out hailMessage))
                        {
                            sessions.Add(inc.SenderConnection, new Session(inc.SenderConnection, this));
                            inc.SenderConnection.Approve(hailMessage);
                        }
                        else
                            inc.SenderConnection.Deny("No !");

                        break;
                    case NetIncomingMessageType.Data:
                        Session session = null;
                        if (sessions.TryGetValue(inc.SenderConnection, out session))
                        {
                            session.HandlePacket(inc);
                        }
                        break;
                    case NetIncomingMessageType.VerboseDebugMessage:
                    case NetIncomingMessageType.DebugMessage:
                        Logger.Debug(inc.ReadString());
                        break;
                    case NetIncomingMessageType.WarningMessage:
                        Logger.Warn(inc.ReadString());
                        break;
                    case NetIncomingMessageType.ErrorMessage:
                        Logger.Error(inc.ReadString());
                        break;
                }
                server.Recycle(inc);
            }
        }

        public NetOutgoingMessage CreateMessage()
        {
            return server.CreateMessage();
        }

        public int SessionCount
        {
            get { return sessions.Count; }
        }

        public NetServer Server
        {
            get { return server; }
        }

        public GameWorld World
        {
            get { return world; }
        }

        public string Name
        {
            get;
            set;
        }
    }
}
