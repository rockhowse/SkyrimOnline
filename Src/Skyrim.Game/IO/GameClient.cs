using Lidgren.Network;
using Skyrim.API;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Text;
using System.Threading.Tasks;

namespace Skyrim.Game.IO
{
    public class Player
    {
        public String playerName;
        public bool isLoaded;

        public Player(String pPlayerName)
        {
            playerName = pPlayerName;
            isLoaded = false;
        }

    }

    public class GameClient
    {
        private static NetClient g_client;
        private static IPEndPoint g_gameServer;
        public bool connected;

        //public static Dictionary<long, Player> g_playerList;

        public delegate void ConnectionSuccessHandler();
        public event ConnectionSuccessHandler ConnectionSuccess;

        public GameClient(IPEndPoint gameServer)
        {
            connected = false;

            NetPeerConfiguration config = new NetPeerConfiguration("game");
            config.EnableMessageType(NetIncomingMessageType.UnconnectedData);
            config.EnableMessageType(NetIncomingMessageType.NatIntroductionSuccess);

            g_client = new NetClient(config);
            g_client.Start();

            g_gameServer = gameServer;
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
                                ConnectionSuccess();
                                break;
                            case NetConnectionStatus.Disconnected:
                            case NetConnectionStatus.Disconnecting:
                            case NetConnectionStatus.InitiatedConnect:
                            case NetConnectionStatus.ReceivedInitiation:
                            case NetConnectionStatus.RespondedAwaitingApproval:
                            case NetConnectionStatus.RespondedConnect:
                                Console.WriteLine(status.ToString());
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
            }
        }

    }
}
