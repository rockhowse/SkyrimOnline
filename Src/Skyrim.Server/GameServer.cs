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

        public GameServer(string pName)
        {
            Name = pName;
            NetPeerConfiguration config = new NetPeerConfiguration("game");
            config.EnableMessageType(NetIncomingMessageType.ConnectionApproval);
            config.EnableMessageType(NetIncomingMessageType.StatusChanged);
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
                    //Report changes in connection status
                    case NetIncomingMessageType.StatusChanged:
                        NetConnectionStatus status = (NetConnectionStatus)inc.ReadByte();
                        switch (status)
                        {
                            case NetConnectionStatus.Connected:
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
                    //Check for client attempting to connect
                    case NetIncomingMessageType.ConnectionApproval:
                        //Send client approval - need to add proper validation later for Deny() cases
                        //Can also use custom hail in approval process
                        inc.SenderConnection.Approve();
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
