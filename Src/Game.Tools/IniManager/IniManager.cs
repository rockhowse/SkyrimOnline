using IniParser;
using log4net;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;

/* * * * * * * * * * * * * * * * * * * * * * *
 * Put ini Object to Container after create
 * Get ini Object from Container
 * * * * * * * * * * * * * * * * * * * * * * */

namespace Game.Tools.IniManager
{
    public class IniManager
    {

        private static Dictionary<string, IniData> iniContainer = null;
        private static readonly ILog Logger = LogManager.GetLogger(MethodBase.GetCurrentMethod().DeclaringType);
        private static volatile IniManager instance;
        private static object syncRoot = new Object();
        private static object syncContainer = new Object();
        private static string lastIniFile = null;
        private static IniData lastData = null;

        private IniManager()
        {
            iniContainer = new Dictionary<string, IniData>();
        }

        public static IniManager Instance
        {
            get
            {
                if (instance == null)
                {
                    lock (syncRoot)
                    {
                        if (instance == null)
                            instance = new IniManager();
                    }
                }

                return instance;
            }
        }

        /// <summary>
        /// EN: Method return IniData from ini file and add to container or from container if exist in container
        /// </summary>
        /// <param name="iniFile">File ini path</param>
        /// <returns>IniData object</returns>
        public IniData getIniData(string iniFile) 
        {

            if (iniFile != null)
            {

                lock (syncContainer)
                {

                    if (lastIniFile != null && lastIniFile.Equals(iniFile) && lastData != null)
                    {
                            return lastData; 
                    }
                    else 
                    {
                        IniData data = null;

                        if (isContainerNotEmpty() && iniContainer.ContainsKey(iniFile))
                        {
                            data = iniContainer[iniFile];
                        }

                        if (data == null)
                        {

                            try
                            {
                                IniParser.FileIniDataParser parser = new IniParser.FileIniDataParser();
                                data = parser.LoadFile(iniFile);
                            }
                            catch (System.Exception ex)
                            {
                                Logger.Error(ex.Message);
                            }

                            if (data != null)
                            {

                                lastIniFile = iniFile;
                                iniContainer.Add(iniFile, data);
                                lastData = data;
                                return data;

                            }
                            else
                            {
                                return null;
                            }

                        }

                    }
                }
            }

            return null;
            
        }

        private bool isContainerNotEmpty() {
            return iniContainer.Count > 0;
        }

        private void SaveFile()
        {

        }

    }
}
