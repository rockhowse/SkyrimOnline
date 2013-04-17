using RGiesecke.DllExport;
using Skyrim.API;
using Skyrim.Script;

namespace Skyrim.Game
{
    public class Entry
    {
        private static IWorld instance = null;
        private static IO.InputManager inputManager = null;

        [DllExport]
        private static void Initialize()
        {
            if (instance == null)
                instance = new World();
            if (inputManager == null)
                inputManager = new IO.InputManager();
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
    }
}
