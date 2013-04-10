using RGiesecke.DllExport;
using Skyrim.Script.Wrapper;

namespace Skyrim.Game
{
    public class Entry
    {
        private static IWorld instance = null;

        [DllExport]
        private static void Initialize()
        {
            if (instance == null)
                instance = new World();
        }

        [DllExport]
        private static void Update()
        {
            Actor player = Skyrim.Script.Papyrus.Game.GetPlayer();

            Skyrim.Script.Papyrus.Debug.Notification("Form ID : " + player.FormID);
        }

        IWorld World
        {
            get { return instance; }
        }
    }
}
