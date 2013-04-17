using Lidgren.Network;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Skyrim.Server
{
    class GameServer
    {
        private NetServer server;

        public GameServer()
        {
            NetPeerConfiguration config = new NetPeerConfiguration("game");
            config.Port = 14242;

            server = new NetServer(config);
            server.Start();
        }

        public void Update()
        {
            NetIncomingMessage inc;
            while ((inc = server.ReadMessage()) != null)
            {
                switch (inc.MessageType)
                {
                    case NetIncomingMessageType.VerboseDebugMessage:
                    case NetIncomingMessageType.DebugMessage:
                    case NetIncomingMessageType.WarningMessage:
                    case NetIncomingMessageType.ErrorMessage:
                        Console.WriteLine(inc.ReadString());
                        break;
                }
            }
        }

        public NetServer Server
        {
            get { return server; }
        }
    }
}
