#region

using System;
using Game.Tools.IniManager;

#endregion

namespace Game.Tools
{
    public class GameTools
    {
        private static readonly string Version = "0.0.5";
        private static IniLoader loader = null;
        private static IniWriter writer = null;

        // I doubt this has the expected behavior
        public static readonly string CompileDate = DateTime.Now.ToString();
    }
}