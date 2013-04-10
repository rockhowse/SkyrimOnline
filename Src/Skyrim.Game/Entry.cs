using RGiesecke.DllExport;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Diagnostics;
using SkyrimScript.Wrapper;

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
            
            Actor player = SkyrimScript.Papyrus.Game.GetPlayer();

            SkyrimScript.Papyrus.Debug.Notification("Form ID : " + player.FormID);

        }
    }
}
