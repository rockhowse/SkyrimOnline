using RGiesecke.DllExport;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Diagnostics;

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
            SkyrimScript.Wrapper.Debug.Notification("TEST " + Stopwatch.GetTimestamp());
        }
    }
}
