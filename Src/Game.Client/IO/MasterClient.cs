using Lidgren.Network;
using Game.API;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Game.Client.IO
{
    public class MasterClient
    {
        private NetClient m_client;
		private IPEndPoint m_masterServer;
        private Guid m_token;

        public Dictionary<long, Object[]> m_registeredHosts;

        public delegate void ServerHandler(Object[] server);
        public event ServerHandler Updated;

        public delegate void NatIntroductionHandler(IPEndPoint endpoint);
        public event NatIntroductionHandler NatIntroductionSuccess;

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
                        MessageBox.Show(inc.ReadString());
                        break;
                    case NetIncomingMessageType.UnconnectedData:
                        if (inc.SenderEndpoint.Equals(m_masterServer))
                        {
                            var id = inc.ReadInt64();
                            var name = inc.ReadString();
                            var population = inc.ReadUInt16();
                            var maxPopulation = inc.ReadUInt16();
                            var ipEndPoint = inc.ReadIPEndpoint();

                            m_registeredHosts.Add(id, new Object[] { name, population, maxPopulation, ipEndPoint }); 
                            Updated(new Object[] { id, name, population, maxPopulation, ipEndPoint });
                        }
                        break;
                    case NetIncomingMessageType.NatIntroductionSuccess:
                        string token = inc.ReadString();
                        if(m_token == new Guid(token))
                            NatIntroductionSuccess(inc.SenderEndpoint);
                        break;
                }
            }
        }

        public IPEndPoint GetServerIPByKey(long gameServerKey)
        {
            Object[] gameServer;
            if (m_registeredHosts.TryGetValue(gameServerKey, out gameServer))
            {
                return (IPEndPoint) gameServer.GetValue(3);
            }

            return null;
        }

        public void GetServerList(string masterServerAddress)
        {
            m_masterServer = new IPEndPoint(NetUtility.Resolve(masterServerAddress), MasterServer.MasterServerPort);

            NetOutgoingMessage listRequest = m_client.CreateMessage();
            listRequest.Write((byte)MasterServerMessageType.RequestHostList);
            listRequest.Write(GlobalContext.Module.Name.ToUpper().GetHashCode());
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

            m_token = Guid.NewGuid();

            om.Write(m_token.ToString());

            m_client.SendUnconnectedMessage(om, m_masterServer);
        }
    }
}
