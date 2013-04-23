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

namespace Game.Server
{
    class GameServer
    {
        private NetServer server;
        private PlayerManager playerManager;
        private GameTime appTime;

        public GameServer(string pName)
        {
            Name = pName;
            NetPeerConfiguration config = new NetPeerConfiguration("game");
            config.EnableMessageType(NetIncomingMessageType.ConnectionApproval);
            config.EnableMessageType(NetIncomingMessageType.StatusChanged);
            config.EnableMessageType(NetIncomingMessageType.Data);
            config.Port = 14242;

            server = new NetServer(config);
            server.Start();

            this.Initialize();   

        }

        protected void Initialize()
        {
            appTime = new GameTime();
            this.playerManager = new PlayerManager(true);
            this.playerManager.PlayerStateChanged += (sender, e) => this.SendMessage(new UpdatePlayerStateMessage(e.Player));
        }

        public void SendMessage(IGameMessage gameMessage)
        {
            NetOutgoingMessage om = this.server.CreateMessage();
            om.Write((byte)gameMessage.MessageType);
            gameMessage.Encode(om);

            this.server.SendToAll(om, NetDeliveryMethod.ReliableUnordered);
        }

        public void Update()
        {
            ProcessNetworkMessages();

            this.playerManager.Update(this.appTime);
        }

        private void ProcessNetworkMessages()
        {
            NetIncomingMessage inc;
            while ((inc = server.ReadMessage()) != null)
            {
                switch (inc.MessageType)
                {
                    //Report changes in connection status
                    case NetIncomingMessageType.StatusChanged:
                        NetConnectionStatus status = (NetConnectionStatus)inc.ReadByte();
                        switch (status)
                        {
                            case NetConnectionStatus.Connected:
                                Console.WriteLine("{0} Connected", inc.SenderEndPoint);
                                break;
                            case NetConnectionStatus.Disconnected:
                                Console.WriteLine("{0} Disconnected", inc.SenderEndPoint);
                                break;
                            case NetConnectionStatus.RespondedAwaitingApproval:
                            case NetConnectionStatus.Disconnecting:
                            case NetConnectionStatus.InitiatedConnect:
                            case NetConnectionStatus.ReceivedInitiation:
                            case NetConnectionStatus.RespondedConnect:
                                Console.WriteLine(status.ToString());
                                break;
                        }
                        break;
                    //Check for client attempting to connect
                    case NetIncomingMessageType.ConnectionApproval:
                        NetOutgoingMessage hailMessage = server.CreateMessage();
                        new UpdatePlayerStateMessage(this.playerManager.AddPlayer(false)).Encode(hailMessage);
                        inc.SenderConnection.Approve(hailMessage);
                        break;
                    case NetIncomingMessageType.Data:
                        var gameMessageType = (GameMessageTypes)inc.ReadByte();
                        switch (gameMessageType)
                        {
                            case GameMessageTypes.UpdatePlayerState:
                                this.HandleUpdatePlayerStateMessage(inc);
                                break;
                        }
                        break;
                    case NetIncomingMessageType.VerboseDebugMessage:
                    case NetIncomingMessageType.DebugMessage:
                    case NetIncomingMessageType.WarningMessage:
                    case NetIncomingMessageType.ErrorMessage:
                        Console.WriteLine(inc.ReadString());
                        break;
                }
                server.Recycle(inc);
            }
        }

        private void HandleUpdatePlayerStateMessage(NetIncomingMessage im)
        {
            var message = new UpdatePlayerStateMessage(im);

            var timeDelay = (float)(NetTime.Now - im.SenderConnection.GetLocalTime(message.MessageTime));

            Player player = this.playerManager.GetPlayer(message.Id)
                            ??
                            this.playerManager.AddPlayer(
                                message.Id, message.Position, message.Velocity, message.Rotation, false);

            player.EnableSmoothing = true;

            if (player.LastUpdateTime < message.MessageTime)
            {
                player.SimulationState.Position = message.Position += message.Velocity * timeDelay;
                player.SimulationState.Velocity = message.Velocity;
                player.SimulationState.Rotation = message.Rotation;

                player.LastUpdateTime = message.MessageTime;
            }
        }

        public NetServer Server
        {
            get { return server; }
        }

        public string Name
        {
            get;
            set;
        }
    }
}
