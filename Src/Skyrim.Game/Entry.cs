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
        private static UserInterace userInterface = null;

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
                if (userInterface == null)
                {
                    userInterface = new UserInterace();
                    userInterface.Chat = new ChatInterface();
                }

                GameClient.Update();
                inputManager.Update();
                userInterface.Update();
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

        static public bool Enabled
        {
            get;
            set;
        }

        static public GameClient GameClient
        {
            get;
            set;
        }
    }
}
