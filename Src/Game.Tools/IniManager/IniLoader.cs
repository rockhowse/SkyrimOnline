using System;
using IniParser;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using log4net;
using log4net.Config;
using System.Reflection;

namespace Game.Tools.IniManager
{
    public class IniLoader
    {

        
        private IniData data = null;

        private static readonly ILog Logger = LogManager.GetLogger(MethodBase.GetCurrentMethod().DeclaringType);

        public IniLoader(IniData iniData)
        {

            if (iniData != null)
            {
                data = iniData;
            }
            
        }

        public IniData getData() 
        {
            return data;
        }

        /// <summary>
        /// EN: Method return String value from config
        /// </summary>
        /// <param name="data"></param>
        /// <param name="section"></param>
        /// <param name="key"></param>
        /// <param name="defaultString"></param>
        /// <returns></returns>
        public string GetValue(string section, string key, string defaultString)
        {
            if (data != null)
            {
                var general = data.Sections.GetSectionData(section);
                if (general != null)
                {
                    if (general.Keys.ContainsKey(key))
                    {
                        var keyData = general.Keys.GetKeyData(key);
                        if (keyData != null && keyData.Value.Length > 0)
                        {
                            return keyData.Value;
                        }
                    }
                }
            }
            return defaultString;
        }

        /// <summary>
        /// EN: Method return Int value from config
        /// </summary>
        /// <param name="data"></param>
        /// <param name="section"></param>
        /// <param name="key"></param>
        /// <param name="defaultValue"></param>
        /// <returns></returns>
        public int GetValue(string section, string key, int defaultValue)
        {
            if (data != null)
            {
                var general = data.Sections.GetSectionData(section);
                if (general != null)
                {
                    if (general.Keys.ContainsKey(key))
                    {
                        var keyData = general.Keys.GetKeyData(key);
                        if (keyData != null && keyData.Value.Length > 0)
                        {
                            return int.Parse(keyData.Value);
                        }
                    }
                }
            }
            return defaultValue;
        }

        /// <summary>
        /// EN: Method return Boolean value from config
        /// </summary>
        /// <param name="data"></param>
        /// <param name="section"></param>
        /// <param name="key"></param>
        /// <param name="defaultValue"></param>
        /// <returns></returns>
        public bool GetValue(string section, string key, bool defaultValue)
        {
            if (data != null)
            {
                var general = data.Sections.GetSectionData(section);
                if (general != null)
                {
                    if (general.Keys.ContainsKey(key))
                    {
                        var keyData = general.Keys.GetKeyData(key);
                        if (keyData != null && (keyData.Value.Length == 4 || keyData.Value.Length == 5))
                        {
                            return bool.Parse(keyData.Value.ToLower());
                        }
                    }
                }
            }
            return defaultValue;
        }


    }
}
