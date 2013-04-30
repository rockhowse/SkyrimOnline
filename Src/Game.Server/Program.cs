using Game.Server.Internals;
using IniParser;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Game.Server
{
    class Program
    {
        static string GetValue(IniData data, string section, string key, string defaultString)
        {
            if (data != null)
            {
                var general = data.Sections.GetSectionData(section);
                if (general != null)
                {
                    if (general.Keys.ContainsKey(key))
                    {
                        var keyData = general.Keys.GetKeyData(key);
                        if (keyData != null && keyData.Value.Length > 0)
                        {
                            return keyData.Value;
                        }
                    }
                }
            }
            return defaultString;
        }

        static int GetValue(IniData data, string section, string key, int defaultValue)
        {
            if (data != null)
            {
                var general = data.Sections.GetSectionData(section);
                if (general != null)
                {
                    if (general.Keys.ContainsKey(key))
                    {
                        var keyData = general.Keys.GetKeyData(key);
                        if (keyData != null && keyData.Value.Length > 0)
                        {
                            return int.Parse(keyData.Value);
                        }
                    }
                }
            }
            return defaultValue;
        }

        static GameServer CreateServer()
        {
            IniData data = null;
            try
            {
                IniParser.FileIniDataParser parser = new IniParser.FileIniDataParser();
                data = parser.LoadFile("GameServer.ini");
            }
            catch (System.Exception ex)
            {
                Console.WriteLine(ex.Message);
            }

            return new GameServer(
                GetValue(data, "General", "Name", "Default server name"),
                GetValue(data, "General", "Port", 14242));
            
        }

        static void Main(string[] args)
        {
            GameServer server =  CreateServer();
            MasterServer masterServer = new MasterServer(server);

            while (Console.KeyAvailable == false || Console.ReadKey().Key != ConsoleKey.Escape)
            {
                server.Update();
                masterServer.Update();

                System.Threading.Thread.Sleep(1);
            }
        }
    }
}
