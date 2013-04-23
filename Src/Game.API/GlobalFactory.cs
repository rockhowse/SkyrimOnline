using Game.API.Utilities;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;

namespace Game.API
{
    public static class GlobalFactory
    {
        private static IModule m_module = null;

        public IModule Module
        {
            get
            {
                if (m_module == null)
                {
                    Module mod = Assembly.GetExecutingAssembly().GetModules()[0];

                    if (mod.Name == "Oblivion.exe")
                        m_module = new OblivionModule();
                    else if (mod.Name == "TESV.exe")
                        m_module = new SkyrimModule();
                }
                return m_module;
            }
        }
    }
}
