#region

using System;

#endregion

namespace Game.Server
{
    public class ServerConfig
    {
        public static readonly string SERVER_CONFIG_FILE = "GameServer.ini";

        public static readonly string SECTION_MASTER = "Master";
        public static readonly string MASTER_KEY_GUID = "GUID";

        public static readonly string SECTION_GENERAL = "General";
        public static readonly string GENERAL_KEY_GAME = "Game";
        public static readonly string GENERAL_KEY_NAME = "Name";
        public static readonly string GENERAL_KEY_ADDRESS = "Address";
        public static readonly string GENERAL_KEY_PORT = "Port";
        public static readonly string GENERAL_KEY_ONLINE = "Online";
        public static readonly string GENERAL_KEY_LANGUAGE = "Language";
        public static readonly string GENERAL_KEY_PASSWORD = "Password";
        private readonly string Address = "127.0.0.1";
        private readonly string GUID = "";

        private readonly int Game;
        private readonly string Language = "English";
        private readonly string Name = "Server Name";
        private readonly bool Online = true;
        private readonly string Password = "";
        private readonly int Port = 14242;

        private ServerConfig()
        {
        }

        public ServerConfig(string game,
            string name,
            string address,
            int port,
            bool online,
            string language,
            string password,
            string guid)
        {
            if (game != null)
            {
                Game = GetHash(game.ToUpper());
            }

            if (name != null)
            {
                Name = name;
            }

            if (address != null)
            {
                Address = address;
            }

            if (port > 1)
            {
                Port = port;
            }

            Online = online;

            if (language != null)
            {
                Language = language;
            }

            if (password != null)
            {
                Password = password;
            }

            if (guid != null)
            {
                GUID = guid;
            }
        }

        public int getGame()
        {
            return Game;
        }

        public string getServerName()
        {
            return Name;
        }

        public string getServerAddress()
        {
            return Address;
        }

        public int getServerPort()
        {
            return Port;
        }

        public bool isOnlineVisible()
        {
            return Online;
        }

        public string getServerLanguage()
        {
            return Language;
        }

        public string getServerPassword()
        {
            return Password;
        }

        public string getGUID()
        {
            return GUID;
        }


        private static Int32 GetHash(string game)
        {
            switch (game)
            {
                case "SKYRIM":
                    return 2095065945;
                case "OBLIVION":
                    return 1663201550;
            }
            return 1663201550;
        }
    }
}