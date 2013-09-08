using Game.Tools.IniManager;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Game.Tools
{

    public class GameTools
    {
        private static readonly string Version = "0.0.5";
        private static IniLoader loader = null;
        private static IniWriter writer = null;
        public static readonly string compileDate = DateTime.Now.ToString();
    }

}
