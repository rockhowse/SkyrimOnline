#region

using System;
using System.Net;
using Game.API.Managers;
using Game.API.Networking;
using Game.API.Networking.Messages;
using Lidgren.Network;
using Microsoft.Xna.Framework;

#endregion

namespace Game.Client.IO
{
    public partial class GameClient
    {
        public delegate void ConnectionHandler(string message);

        private readonly NetClient client;
        private readonly IPEndPoint gameServer;
        private readonly PacketHandler handler = new PacketHandler();
        private GameTime appTime;

        public bool connected;
        private PlayerManager playerManager;

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

            Initialize();
        }

        public event ConnectionHandler ConnectionSuccess;
        public event ConnectionHandler ConnectionFailed;

        protected void Initialize()
        {
            appTime = new GameTime();

            handler.OnChatTalk += HandleChatTalkMessage;

            playerManager = new PlayerManager(false);
            playerManager.PlayerStateChanged += (sender, e) => SendMessage(new UpdatePlayerStateMessage(e.Player));
        }

        public void SendMessage(IGameMessage gameMessage)
        {
            NetOutgoingMessage om = client.CreateMessage();
            om.Write((byte) gameMessage.MessageType);
            gameMessage.Encode(om);

            client.SendMessage(om, NetDeliveryMethod.ReliableUnordered);
        }

        public void SendMessageOrdered(IGameMessage gameMessage)
        {
            NetOutgoingMessage om = client.CreateMessage();
            om.Write((byte) gameMessage.MessageType);
            gameMessage.Encode(om);

            client.SendMessage(om, NetDeliveryMethod.ReliableOrdered);
        }

        public void Connect()
        {
            if (gameServer != null)
            {
                connected = true;
                //Attempt to connect to the remote server
                NetOutgoingMessage om = client.CreateMessage();
                IGameMessage gameMessage = new HandShakeMessage
                {
                    Version = PacketHandler.PROTOCOL_VERSION,
                    Username = Entry.Username
                };

                om.Write((byte) gameMessage.MessageType);
                gameMessage.Encode(om);

                client.Connect(gameServer, om);
            }
        }

        public void Update()
        {
            ProcessNetworkMessages();

            playerManager.Update(appTime);
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
                        NetConnectionStatus status = (NetConnectionStatus) inc.ReadByte();
                        switch (status)
                        {
                            case NetConnectionStatus.Connected:
                                /*var message = new UpdatePlayerStateMessage(inc.SenderConnection.RemoteHailMessage);
                                this.playerManager.AddPlayer(message.Id, message.Position, message.Velocity, message.Rotation, true);
                                Console.WriteLine("Connected to {0}", inc.SenderEndPoint);*/
                                ConnectionSuccess("Connected to " + inc.SenderEndpoint);
                                break;
                            case NetConnectionStatus.Disconnected:
                                if (Entry.UserInterace != null && Entry.UserInterace.Chat != null)
                                    Entry.UserInterace.Chat.Log("Lost connection to the server !");

                                string reason = "Unknown error !";
                                try
                                {
                                    inc.ReadByte();
                                    reason = inc.ReadString();
                                }
                                catch
                                {
                                }

                                ConnectionFailed(reason);
                                break;
                            case NetConnectionStatus.Disconnecting:
                            case NetConnectionStatus.InitiatedConnect:
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