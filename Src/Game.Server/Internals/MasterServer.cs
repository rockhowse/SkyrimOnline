#region

using System;
using System.IO;
using System.Net;
using System.Reflection;
using Game.API;
using Lidgren.Network;
using log4net;

#endregion

namespace Game.Server.Internals
{
    internal class MasterServerClient
    {
        private static readonly ILog Logger = LogManager.GetLogger(MethodBase.GetCurrentMethod().DeclaringType);
        private readonly string mGuid = "none";

        private readonly IPEndPoint masterServerEndpoint;
        private readonly GameServer server;
        private float lastRegistered = -60.0f;
        private string mIp;

        public MasterServerClient(GameServer pServer, string guid)
        {
            server = pServer;
            mGuid = guid;
            masterServerEndpoint = NetUtility.Resolve("game.skyrim-online.com", MasterServer.MasterServerPort);
        }

        public string GetPublicIP()
        {
            while (mIp == null)
            {
                try
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
                    mIp = direction.Substring(first, last - first);
                }
                catch
                {
                }
            }

            return mIp;
        }

        public void Update()
        {
            if (NetTime.Now > lastRegistered + 60)
            {
                NetOutgoingMessage regMsg = server.Server.CreateMessage();
                regMsg.Write((byte) MasterServerMessageType.RegisterHost);

                IPAddress adr = IPAddress.Parse(GetPublicIP());

                regMsg.Write(server.Server.UniqueIdentifier);
                regMsg.Write(server.Name);
                regMsg.Write((UInt16) server.Server.ConnectionsCount);
                regMsg.Write((UInt16) 1000);
                regMsg.Write(mGuid);
                regMsg.Write(new IPEndPoint(adr, server.Server.Port));
                regMsg.Write(Program.Game);

                Logger.Debug("Sending registration to master server");
                server.Server.SendUnconnectedMessage(regMsg, masterServerEndpoint);
                lastRegistered = (float) NetTime.Now;
            }
        }
    }
}