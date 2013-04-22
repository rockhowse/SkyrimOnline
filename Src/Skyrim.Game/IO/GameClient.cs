using Lidgren.Network;
using Skyrim.API;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Text;
using System.Threading.Tasks;
using Skyrim.API.Managers;
using Skyrim.API.Entities;
using Skyrim.API.Networking;
using Skyrim.API.Networking.Messages;
using Microsoft.Xna.Framework;

namespace Skyrim.Game.IO
{
    public class GameClient
    {
        private static NetClient g_client;
        private static IPEndPoint g_gameServer;
        private PlayerManager playerManager;
        private GameTime appTime;

        public bool connected;

        //public static Dictionary<long, Player> g_playerList;

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

            g_client = new NetClient(config);
            g_client.Start();

            g_gameServer = gameServer;

            this.Initialize();
        }

        protected void Initialize()
        {
            appTime = new GameTime();
            this.playerManager = new PlayerManager(false);
            this.playerManager.PlayerStateChanged += (sender, e) => this.SendMessage(new UpdatePlayerStateMessage(e.Player));
        }

        public void SendMessage(IGameMessage gameMessage)
        {
            NetOutgoingMessage om = g_client.CreateMessage();
            om.Write((byte)gameMessage.MessageType);
            gameMessage.Encode(om);

            g_client.SendMessage(om, NetDeliveryMethod.ReliableUnordered);
        }

        public void Connect()
        {
            if (g_gameServer != null)
            {
                connected = true;
                //Attempt to connect to the remote server
                g_client.Connect(g_gameServer);
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
            while ((inc = g_client.ReadMessage()) != null)
            {
                switch (inc.MessageType)
                {
                    //Report changes in connection status
                    case NetIncomingMessageType.StatusChanged:
                        NetConnectionStatus status = (NetConnectionStatus)inc.ReadByte();
                        switch (status)
                        {
                            case NetConnectionStatus.Connected:
                                var message = new UpdatePlayerStateMessage(inc.SenderConnection.RemoteHailMessage);
                                this.playerManager.AddPlayer(message.Id, message.Position, message.Velocity, message.Rotation, true);
                                Console.WriteLine("Connected to {0}", inc.SenderEndPoint);
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
                        NetOutgoingMessage hailMessage = g_client.CreateMessage();
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
                g_client.Recycle(inc);
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

    }
}
