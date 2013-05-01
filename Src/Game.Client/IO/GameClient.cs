using Lidgren.Network;
using Game.API;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Text;
using System.Threading.Tasks;
using Game.API.Managers;
using Game.API.Entities;
using Game.API.Networking;
using Game.API.Networking.Messages;
using Microsoft.Xna.Framework;

namespace Game.Client.IO
{
    public partial class GameClient
    {
        private NetClient client;
        private IPEndPoint gameServer;
        private PlayerManager playerManager;
        private GameTime appTime;
        private PacketHandler handler = new PacketHandler();

        public bool connected;

        public delegate void ConnectionHandler();
        public event ConnectionHandler ConnectionSuccess;
        public event ConnectionHandler ConnectionFailed;

        public GameClient(IPEndPoint gameServer)
        {
            connected = false;

            NetPeerConfiguration config = new NetPeerConfiguration("game");
            config.EnableMessageType(NetIncomingMessageType.UnconnectedData);
            config.EnableMessageType(NetIncomingMessageType.NatIntroductionSuccess);
            config.EnableMessageType(NetIncomingMessageType.ConnectionApproval);
            config.EnableMessageType(NetIncomingMessageType.Data);

            client = new NetClient(config);
            client.Start();

            this.gameServer = gameServer;

            this.Initialize();
        }

        protected void Initialize()
        {
            appTime = new GameTime();

            this.handler.OnChatTalk += HandleChatTalkMessage;

            this.playerManager = new PlayerManager(false);
            this.playerManager.PlayerStateChanged += (sender, e) => this.SendMessage(new UpdatePlayerStateMessage(e.Player));
        }

        public void SendMessage(IGameMessage gameMessage)
        {
            NetOutgoingMessage om = client.CreateMessage();
            om.Write((byte)gameMessage.MessageType);
            gameMessage.Encode(om);

            client.SendMessage(om, NetDeliveryMethod.ReliableUnordered);
        }

        public void Connect()
        {
            if (gameServer != null)
            {
                connected = true;
                //Attempt to connect to the remote server
                client.Connect(gameServer);
            }
        }

        public void Update()
        {
            ProcessNetworkMessages();

            this.playerManager.Update(this.appTime);
        }

        private void ProcessNetworkMessages()
        {
            NetIncomingMessage inc;
            while ((inc = client.ReadMessage()) != null)
            {
                switch (inc.MessageType)
                {
                    //Report changes in connection status
                    case NetIncomingMessageType.StatusChanged:
                        NetConnectionStatus status = (NetConnectionStatus)inc.ReadByte();
                        switch (status)
                        {
                            case NetConnectionStatus.Connected:
                                /*var message = new UpdatePlayerStateMessage(inc.SenderConnection.RemoteHailMessage);
                                this.playerManager.AddPlayer(message.Id, message.Position, message.Velocity, message.Rotation, true);
                                Console.WriteLine("Connected to {0}", inc.SenderEndPoint);*/
                                ConnectionSuccess();
                                break;
                            case NetConnectionStatus.Disconnected:
                                Console.WriteLine("Disconnected from {0}", inc.SenderEndPoint);
                                ConnectionFailed();
                                break;
                            case NetConnectionStatus.Disconnecting:
                            case NetConnectionStatus.InitiatedConnect:
                            case NetConnectionStatus.ReceivedInitiation:
                            case NetConnectionStatus.RespondedAwaitingApproval:
                            case NetConnectionStatus.RespondedConnect:
                                Console.WriteLine(status.ToString());
                                break;
                        }
                        break;
                    case NetIncomingMessageType.ConnectionApproval:

                        break;
                    case NetIncomingMessageType.Data:
                        handler.Handle(inc);
                        break;
                    case NetIncomingMessageType.VerboseDebugMessage:
                    case NetIncomingMessageType.DebugMessage:
                    case NetIncomingMessageType.WarningMessage:
                    case NetIncomingMessageType.ErrorMessage:
                        Console.WriteLine(inc.ReadString());
                        break;
                }
                client.Recycle(inc);
            }
        }

    }
}
