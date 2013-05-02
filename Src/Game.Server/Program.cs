using Game.Server.Internals;
using IniParser;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using log4net;
using log4net.Config;
using System.Reflection;

namespace Game.Server
{
    class Program
    {
        private static readonly ILog Logger = LogManager.GetLogger(MethodBase.GetCurrentMethod().DeclaringType);


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
                Logger.Error(ex.Message);
            }

            return new GameServer(
                GetValue(data, "General", "Name", "Default server name"),
                GetValue(data, "General", "Port", 14242));

        }

        static MasterServerClient CreateMasterServerClient(GameServer server)
        {
            IniData data = null;
            try
            {
                IniParser.FileIniDataParser parser = new IniParser.FileIniDataParser();
                data = parser.LoadFile("GameServer.ini");
            }
            catch (System.Exception ex)
            {
                Logger.Error(ex.Message);
            }

            return new MasterServerClient(server,
                GetValue(data, "Master", "GUID", "none"));

        }

        static void Main(string[] args)
        {
            try
            {
                XmlConfigurator.Configure();

                GameServer server = CreateServer();
                MasterServerClient masterClient = CreateMasterServerClient(server);

                while (Console.KeyAvailable == false || Console.ReadKey().Key != ConsoleKey.Escape)
                {
                    server.Update();
                    masterClient.Update();

                    System.Threading.Thread.Sleep(1);
                }
            }
            catch (System.Exception ex)
            {
                Console.WriteLine(ex.ToString());
            }
        }
    }
}
