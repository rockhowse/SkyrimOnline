#region

using System.IO;
using System.Reflection;
using IniParser;
using IniParser.Model;
using log4net;

#endregion

namespace Game.Tools.IniManager
{
    public class IniLoader
    {
        private static readonly ILog Logger = LogManager.GetLogger(MethodBase.GetCurrentMethod().DeclaringType);
        private readonly IniManager manager = IniManager.Instance;
        private IniData data = null;


        public IniLoader(string iniFilePath)
        {
            if (iniFilePath != null && File.Exists(iniFilePath))
            {
                data = manager.getIniData(iniFilePath);
            }
        }

        /// <summary>
        ///     Force load data from ini file
        /// </summary>
        /// <param name="pathToIni">Path to ini file</param>
        public void ForceLoadData(string pathToIni)
        {
            if (data != null)
            {
                data = manager.forceLoadIniData(pathToIni);
            }
        }

        /// <summary>
        ///     EN: Method return String value from config
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
        ///     EN: Method return Int value from config
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
        ///     EN: Method return Boolean value from config
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