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

        public static Dictionary<long, Player> g_playerList;

        public GameClient(IPEndPoint gameServer)
        {
            NetPeerConfiguration config = new NetPeerConfiguration("game");
            config.EnableMessageType(NetIncomingMessageType.UnconnectedData);
            config.EnableMessageType(NetIncomingMessageType.NatIntroductionSuccess);

            g_client = new NetClient(config);
            g_client.Start();

            g_gameServer = gameServer;
        }

    }
}
