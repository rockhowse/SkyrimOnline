using RGiesecke.DllExport;
using Skyrim.API;
using Skyrim.Game.Interface;
using Skyrim.Game.IO;
using Skyrim.Script;
using System.Windows.Forms;

namespace Skyrim.Game
{
    public class Entry
    {
        private static IWorld instance = null;
        private static IO.InputManager inputManager = null;

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
                instance.Update();
            }
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
