using Game.API.Utilities;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;

namespace Game.API
{
    public static class GlobalContext
    {
        private static IModule m_module = null;

        public static IModule Module
        {
            get
            {
                if (m_module == null)
                {
                    string assemblyName = Process.GetCurrentProcess().MainModule.ModuleName;

                    if (assemblyName == "Oblivion.exe")
                        m_module = new OblivionModule();
                    else if (assemblyName == "TESV.exe")
                        m_module = new SkyrimModule();
                }
                return m_module;
            }
        }

        public static IController Controller
        {
            get;
            set;
        }
    }
}
