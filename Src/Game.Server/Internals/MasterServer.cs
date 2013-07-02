using Lidgren.Network;
using Game.API;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Text;
using System.Threading.Tasks;
using log4net;
using System.Reflection;
using System.IO;

namespace Game.Server.Internals
{
    class MasterServerClient
    {
        private static readonly ILog Logger = LogManager.GetLogger(MethodBase.GetCurrentMethod().DeclaringType);

        IPEndPoint masterServerEndpoint;
        float lastRegistered = -60.0f;
        GameServer server = null;
        string mGuid = "none";

        public MasterServerClient(GameServer pServer, string guid)
        {
            server = pServer;
            mGuid = guid;
            masterServerEndpoint = NetUtility.Resolve("game.skyrim-online.com", Game.API.MasterServer.MasterServerPort);
        }

        public string GetPublicIP()
        {
            String direction = "";
            WebRequest request = WebRequest.Create("http://checkip.dyndns.org/");
            using (WebResponse response = request.GetResponse())
            using (StreamReader stream = new StreamReader(response.GetResponseStream()))
            {
                direction = stream.ReadToEnd();
            }

            //Search for the ip in the html
            int first = direction.IndexOf("Address: ") + 9;
            int last = direction.LastIndexOf("</body>");
            direction = direction.Substring(first, last - first);

            return direction;
        }

        public void Update()
        {
            if (NetTime.Now > lastRegistered + 60)
            {
                NetOutgoingMessage regMsg = server.Server.CreateMessage();
                regMsg.Write((byte)MasterServerMessageType.RegisterHost);

                IPAddress adr = IPAddress.Parse(GetPublicIP());

                regMsg.Write(server.Server.UniqueIdentifier);
                regMsg.Write(server.Name);
                regMsg.Write((UInt16)server.Server.ConnectionsCount);
                regMsg.Write((UInt16)1000);
                regMsg.Write(mGuid);
                regMsg.Write(new IPEndPoint(adr, server.Server.Port));
                regMsg.Write(Program.Game);
                
                Logger.Debug("Sending registration to master server");
                server.Server.SendUnconnectedMessage(regMsg, masterServerEndpoint);
                lastRegistered = (float)NetTime.Now;
            }
        }
    }
}
