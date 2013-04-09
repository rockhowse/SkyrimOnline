using RGiesecke.DllExport;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

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
            // Called everytime SkyrimVM's is updated
        }
    }
}
