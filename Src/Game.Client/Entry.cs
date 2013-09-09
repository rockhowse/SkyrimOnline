#region

using System.Windows.Forms;
using Game.API;
using Game.API.Utilities;
using Game.Client.Config;
using Game.Client.Controllers;
using Game.Client.Interface;
using Game.Client.IO;
using RGiesecke.DllExport;

#endregion

namespace Game.Client
{
    public class Entry
    {
        private static IWorld instance;
        private static InputManager inputManager;
        private static bool menuMode = true;

        public static string Username { get; set; }

        public static IWorld World
        {
            get { return instance; }
        }

        public static GameClient GameClient { get; set; }

        public static UserInterace UserInterace { get; set; }

        public static bool Enabled { get; set; }

        [DllExport]
        private static void Load()
        {
        }

        [DllExport]
        private static void Initialize()
        {
            Application.EnableVisualStyles();
            Application.Run(new Play());

            if (Enabled)
            {
                switch (GlobalContext.Module.GameType)
                {
                    case GameType.kOblivion:
                        GlobalContext.Controller = new OblivionController();
                        break;
                    case GameType.kSkyrim:
                        GlobalContext.Controller = new SkyrimController();
                        break;
                }

                if (instance == null)
                    instance = new World();
                if (inputManager == null)
                    inputManager = new InputManager();
            }
        }

        [DllExport]
        private static void Update()
        {
            if (Enabled)
            {
                if (UserInterace == null)
                {
                    UserInterace = new UserInterace();
                    UserInterace.Chat = new ChatInterface();
                }

                GameClient.Update();
                inputManager.Update();
                UserInterace.Update();

                bool menu = GlobalContext.Controller.IsMenuMode();
                if (menuMode != menu)
                {
                    menuMode = menu;
                    if (menuMode)
                    {
                    }
                    else
                    {
                        instance.OnEnter();
                    }
                }

                if (!menu)
                    instance.Update();
            }
        }
    }
}