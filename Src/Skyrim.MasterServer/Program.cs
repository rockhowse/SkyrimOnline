using Lidgren.Network;
using Skyrim.API;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Text;
using System.Threading.Tasks;

namespace Skyrim.MasterServer
{
    class Program
    {
        static void Main(string[] args)
        {
            Dictionary<long, Object[]> registeredHosts = new Dictionary<long, Object[]>();

            NetPeerConfiguration config = new NetPeerConfiguration("masterserver");
            config.SetMessageTypeEnabled(NetIncomingMessageType.UnconnectedData, true);
            config.Port = Skyrim.API.MasterServer.MasterServerPort;

            NetPeer peer = new NetPeer(config);
            peer.Start();

            Console.WriteLine("Press ESC to quit");
            while (!Console.KeyAvailable || Console.ReadKey().Key != ConsoleKey.Escape)
            {
                NetIncomingMessage msg;
                while ((msg = peer.ReadMessage()) != null)
                {
                    switch (msg.MessageType)
                    {
                        case NetIncomingMessageType.UnconnectedData:
                            switch ((MasterServerMessageType)msg.ReadByte())
                            {
                                case MasterServerMessageType.RegisterHost:

                                    var id = msg.ReadInt64();
                                    var name = msg.ReadString();
                                    var population = msg.ReadUInt16();
                                    var maxPopulation = msg.ReadUInt16();

                                    Console.WriteLine("Got registration for host " + id);
                                    registeredHosts[id] = new Object[]
									{
										msg.ReadIPEndPoint(),
										msg.SenderEndPoint,
                                        name,
                                        population,
                                        maxPopulation,
                                        NetTime.Now
									};
                                    break;

                                case MasterServerMessageType.RequestHostList:
                                    Console.WriteLine("Sending list of " + registeredHosts.Count + " hosts to client " + msg.SenderEndPoint);
                                    List<long> toRemove = new List<long>();
                                    foreach (var kvp in registeredHosts)
                                    {
                                        if ((double)kvp.Value[5] + 130.0 < NetTime.Now)
                                        {
                                            toRemove.Add(kvp.Key);
                                            continue;
                                        }
                                        NetOutgoingMessage om = peer.CreateMessage();
                                        om.Write(kvp.Key);
                                        om.Write((string)kvp.Value[2]);
                                        om.Write((UInt16)kvp.Value[3]);
                                        om.Write((UInt16)kvp.Value[4]);
                                        om.Write((IPEndPoint)kvp.Value[1]);
                                        peer.SendUnconnectedMessage(om, msg.SenderEndPoint);
                                    }

                                    foreach (var kvp in toRemove)
                                    {
                                        registeredHosts.Remove(kvp);
                                    }

                                    break;
                                case MasterServerMessageType.RequestIntroduction:

                                    IPEndPoint clientInternal = msg.ReadIPEndPoint();
                                    long hostId = msg.ReadInt64();
                                    string token = msg.ReadString();

                                    Object[] elist;
                                    if (registeredHosts.TryGetValue(hostId, out elist))
                                    {
                                        peer.Introduce(
                                            (IPEndPoint)elist[0],
                                            (IPEndPoint)elist[1],
                                            clientInternal,
                                            msg.SenderEndPoint, 
                                            token 
                                        );
                                    }
                                    else
                                    {
                                        Console.WriteLine("Client requested introduction to nonlisted host!");
                                    }
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
            }

            peer.Shutdown("shutting down");
        }
    }
}
