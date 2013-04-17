using RGiesecke.DllExport;
using Skyrim.API;
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

            View = new Config.Play();

            Application.Run(View);

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
            inputManager.Update();   
            instance.Update();
        }

        static public IWorld World
        {
            get { return instance; }
        }

        static public bool Enabled
        {
            get;
            set;
        }

        static public Config.Play View
        {
            get;
            set;
        }

        static public IO.MasterClient Client
        {
            get;
            set;
        }
    }
}
