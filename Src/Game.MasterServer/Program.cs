#region

using System;
using System.Collections.Generic;
using System.Net;
using System.Threading;
using Game.API;
using Lidgren.Network;

#endregion

namespace Game.MasterServer
{
    internal class Program
    {
        private readonly ServerManager manager = new ServerManager();
        private readonly NetPeer peer;
        private readonly Dictionary<Int64, Object[]> registeredHosts = new Dictionary<Int64, Object[]>();

        public Program()
        {
            NetPeerConfiguration config = new NetPeerConfiguration("masterserver");
            config.SetMessageTypeEnabled(NetIncomingMessageType.UnconnectedData, true);
            config.Port = API.MasterServer.MasterServerPort;

            peer = new NetPeer(config);
            peer.Start();
        }

        ~Program()
        {
            peer.Shutdown("shutting down");
        }

        private void Update()
        {
            NetIncomingMessage msg;
            while ((msg = peer.ReadMessage()) != null)
            {
                try
                {
                    switch (msg.MessageType)
                    {
                        case NetIncomingMessageType.UnconnectedData:
                            switch ((MasterServerMessageType) msg.ReadByte())
                            {
                                case MasterServerMessageType.RegisterHost:
                                    HandleRegisterHost(msg);
                                    break;

                                case MasterServerMessageType.RequestHostList:
                                    HandleRequestHost(msg);
                                    break;
                                case MasterServerMessageType.RequestIntroduction:
                                    HandleRequestIntroduction(msg);
                                    break;
                            }
                            break;

                        case NetIncomingMessageType.DebugMessage:
                        case NetIncomingMessageType.VerboseDebugMessage:
                        case NetIncomingMessageType.WarningMessage:
                        case NetIncomingMessageType.ErrorMessage:
                            // print diagnostics message
                            Console.WriteLine(msg.ReadString());
                            break;
                    }
                }
                catch
                {
                }
            }
        }

        private void HandleRequestIntroduction(NetIncomingMessage msg)
        {
            IPEndPoint clientInternal = msg.ReadIPEndpoint();
            long hostId = msg.ReadInt64();
            string token = msg.ReadString();

            Object[] elist;
            if (registeredHosts.TryGetValue(hostId, out elist))
            {
                peer.Introduce(
                    (IPEndPoint) elist[0],
                    (IPEndPoint) elist[1],
                    clientInternal,
                    msg.SenderEndpoint,
                    token
                    );
            }
            else
            {
                Console.WriteLine("Client requested introduction to nonlisted host!");
            }
        }

        private void HandleRequestHost(NetIncomingMessage inc)
        {
            Console.WriteLine("Sending list of " + registeredHosts.Count + " hosts to client " + inc.SenderEndpoint);
            List<Int64> toRemove = new List<Int64>();
            var game = inc.ReadInt32();

            foreach (var kvp in registeredHosts)
            {
                if ((double) kvp.Value[5] + 130.0 < NetTime.Now)
                {
                    toRemove.Add(kvp.Key);
                    continue;
                }

                //Console.WriteLine(game + " " + kvp.Value[6]);
                if ((int) kvp.Value[6] == game)
                {
                    NetOutgoingMessage om = peer.CreateMessage();
                    om.Write(kvp.Key);
                    om.Write((string) kvp.Value[2]);
                    om.Write((UInt16) kvp.Value[3]);
                    om.Write((UInt16) kvp.Value[4]);
                    om.Write((IPEndPoint) kvp.Value[1]);
                    peer.SendUnconnectedMessage(om, inc.SenderEndpoint);
                }
            }

            foreach (var kvp in toRemove)
            {
                manager.Release(kvp);
                registeredHosts.Remove(kvp);
            }
        }

        private void HandleRegisterHost(NetIncomingMessage inc)
        {
            var id = inc.ReadInt64();
            var name = inc.ReadString();
            var population = inc.ReadUInt16();
            var maxPopulation = inc.ReadUInt16();
            var guid = inc.ReadString();
            var endpoint = inc.ReadIPEndpoint();
            var game = inc.ReadInt32();

            //if (manager.Register(id, new Guid(guid)))
            {
                registeredHosts[id] = new Object[]
                {
                    endpoint,
                    inc.SenderEndpoint,
                    name,
                    population,
                    maxPopulation,
                    NetTime.Now,
                    game
                };
            }
        }

        private static void Main(string[] args)
        {
            Program prog = new Program();

            Console.WriteLine("Press ESC to quit");
            while (!Console.KeyAvailable || Console.ReadKey().Key != ConsoleKey.Escape)
            {
                prog.Update();
                Thread.Sleep(100);
            }
        }
    }
}