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
    public class MasterClient
    {
        private static NetClient m_client;
		private static IPEndPoint m_masterServer;

        public Dictionary<long, Object[]> m_registeredHosts;

        public delegate void ServerHandler(Object[] server);
        public event ServerHandler Updated;

        public MasterClient()
        {
            m_registeredHosts = new Dictionary<long, Object[]>();

            NetPeerConfiguration config = new NetPeerConfiguration("game");
            config.EnableMessageType(NetIncomingMessageType.UnconnectedData);
            config.EnableMessageType(NetIncomingMessageType.NatIntroductionSuccess);
            m_client = new NetClient(config);
            m_client.Start();
        }

        public void Update()
        {
            NetIncomingMessage inc;
            while ((inc = m_client.ReadMessage()) != null)
            {
                switch (inc.MessageType)
                {
                    case NetIncomingMessageType.VerboseDebugMessage:
                    case NetIncomingMessageType.DebugMessage:
                    case NetIncomingMessageType.WarningMessage:
                    case NetIncomingMessageType.ErrorMessage:
                        break;
                    case NetIncomingMessageType.UnconnectedData:
                        if (inc.SenderEndPoint.Equals(m_masterServer))
                        {
                            var id = inc.ReadInt64();
                            var name = inc.ReadString();
                            var population = inc.ReadUInt16();
                            var maxPopulation = inc.ReadUInt16();

                            m_registeredHosts[id] = new Object[] { name, population, maxPopulation };
                            Updated(new Object[] { id, name, population, maxPopulation });
                        }
                        break;
                    case NetIncomingMessageType.NatIntroductionSuccess:
                        string token = inc.ReadString();
                        break;
                }
            }
        }

        public void GetServerList(string masterServerAddress)
        {
            m_masterServer = new IPEndPoint(NetUtility.Resolve(masterServerAddress), MasterServer.MasterServerPort);

            NetOutgoingMessage listRequest = m_client.CreateMessage();
            listRequest.Write((byte)MasterServerMessageType.RequestHostList);
            m_client.SendUnconnectedMessage(listRequest, m_masterServer);
        }

        public void RequestNATIntroduction(long hostid)
        {
            if (hostid == 0)
            {
                return;
            }

            if (m_masterServer == null)
                throw new Exception("Must connect to master server first!");

            NetOutgoingMessage om = m_client.CreateMessage();
            om.Write((byte)MasterServerMessageType.RequestIntroduction);

            IPAddress mask;
            om.Write(new IPEndPoint(NetUtility.GetMyAddress(out mask), m_client.Port));

            om.Write(hostid);

            om.Write(Guid.NewGuid().ToString());

            m_client.SendUnconnectedMessage(om, m_masterServer);
        }
    }
}
