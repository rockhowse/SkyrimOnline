using Skyrim.Server.Internals;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Skyrim.Server
{
    class Program
    {
        static void Main(string[] args)
        {
            GameServer server = new GameServer();
            MasterServer masterServer = new MasterServer(server.Server);

            while (Console.KeyAvailable == false || Console.ReadKey().Key != ConsoleKey.Escape)
            {
                server.Update();
                masterServer.Update();

                System.Threading.Thread.Sleep(1);
            }
        }
    }
}
