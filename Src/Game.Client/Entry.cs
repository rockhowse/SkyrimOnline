using RGiesecke.DllExport;
using Game.API;
using Game.Client.Interface;
using Game.Client.IO;
using Game.Script;
using System.Windows.Forms;
using Game.Client.Controllers;

namespace Game.Client
{
    public class Entry
    {
        private static IWorld instance = null;
        private static IO.InputManager inputManager;
        private static bool menuMode = true;

        [DllExport]
        private static void Load()
        {
        }

        [DllExport]
        private static void Initialize()
        {
            Application.EnableVisualStyles();
            Application.Run(new Config.Play());

            if (Enabled)
            {
                switch (GlobalContext.Module.GameType)
                {
                    case API.Utilities.GameType.kOblivion:
                        GlobalContext.Controller = new OblivionController();
                        break;
                    case API.Utilities.GameType.kSkyrim:
                        GlobalContext.Controller = new SkyrimController();
                        break;
                }

              if (instance == null)
                   instance = new World();
              if (inputManager == null)
                   inputManager = new IO.InputManager();
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

                if(!menu)
                    instance.Update();
            }
        }

        static public string Username
        {
            get;
            set;
        }

        static public IWorld World
        {
            get 
            { 
                return instance; 
            }
        }

        static public GameClient GameClient
        {
            get;
            set;
        }

        static public UserInterace UserInterace
        {
            get;
            set;
        }

        static public bool Enabled
        {
            get;
            set;
        }
    }
}
