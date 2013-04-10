using RGiesecke.DllExport;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Diagnostics;
using Skyrim.Script.Wrapper;

namespace Skyrim.Game
{
    public class Entry
    {
        [DllExport]
        public static void Initialize()
        {
            // Called upon creation
        }

        [DllExport]
        public static void Update()
        {
            Actor player = Skyrim.Script.Papyrus.Game.GetPlayer();

            Skyrim.Script.Papyrus.Debug.Notification("Form ID : " + player.FormID);

        }
    }
}
