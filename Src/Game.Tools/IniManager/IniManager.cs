using IniParser;
using IniParser.Model;
using log4net;

#region

using System;
using System.Collections.Generic;
using System.IO;
using System.Reflection;

#endregion

/* * * * * * * * * * * * * * * * * * * * * * *
 * Put ini Object to Container after create
 * Get ini Object from Container
 * * * * * * * * * * * * * * * * * * * * * * */

namespace Game.Tools.IniManager
{
    public class IniManager
    {
        private static Dictionary<string, IniData> container;
        private static readonly FileIniDataParser parser = new FileIniDataParser();
        private static readonly ILog Logger = LogManager.GetLogger(MethodBase.GetCurrentMethod().DeclaringType);
        private static volatile IniManager instance;

        private static readonly object syncRoot = new Object();
        private static readonly object syncValue = new Object();
        private static readonly object syncContainer = new Object();

        private static IniData cache = null;
        private static string nameCache;

        private IniManager()
        {
            container = new Dictionary<string, IniData>();
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
        ///     EN: Method return IniData from ini file and add to container or from container if exist in container
        /// </summary>
        /// <param name="iniFile">File ini path</param>
        /// <returns>IniData object</returns>
        public IniData getIniData(string iniFile)
        {
            if (iniFile != null && File.Exists(iniFile))
            {
                // data in cache
                if (isCached(iniFile))
                {
                    getCachedData(iniFile);
                }
                else
                {
                    setDataSetCache(iniFile);
                }

                return cache;
            }

            return null;
        }

        /// <summary>
        ///     EN: Set data and set data to cache
        /// </summary>
        /// <returns>Data from ini file</returns>
        private void setDataSetCache(string pathToIni)
        {
            if (pathToIni != null && File.Exists(pathToIni))
            {
                lock (syncValue)
                {
                    nameCache = pathToIni;
                    cache = parser.ReadFile(pathToIni);
                }

                lock (syncContainer)
                {
                    container.Add(nameCache, cache);
                }
            }
        }

        /// <summary>
        ///     EN: Force loading data from specyfic file without read from cache, but set to temporary cache and add to cache
        ///     container
        /// </summary>
        /// <param name="pathToIni">Path to ini file</param>
        /// <returns>Data from ini file</returns>
        public IniData forceLoadIniData(string pathToIni)
        {
            if (pathToIni != null && File.Exists(pathToIni))
            {
                lock (syncValue)
                {
                    nameCache = pathToIni;
                    cache = parser.ReadFile(pathToIni);
                }

                lock (syncContainer)
                {
                    if (container.Count > 0 && container.ContainsKey(nameCache))
                    {
                        updateContainerValue(nameCache, cache);
                    }
                    else
                    {
                        container.Add(nameCache, cache);
                    }
                }


                return cache;
            }

            return null;
        }

        /// <summary>
        ///     EN: Update cache value in container on specific index
        /// </summary>
        /// <param name="pathToIni">Path to ini file</param>
        /// <param name="data">Data from ini file</param>
        private void updateContainerValue(string pathToIni, IniData data)
        {
            if (pathToIni != null && data != null)
            {
                container[pathToIni] = data;
            }
        }

        /// <summary>
        ///     EN: Checking data is cached in cache or container
        /// </summary>
        /// <param name="pathToIni">Path to ini file</param>
        /// <returns>Return true if data is cached in cache or in container, otherwise false</returns>
        private bool isCached(string pathToIni)
        {
            if (nameCache != null && container.Count > 0)
            {
                if (nameCache.Equals(pathToIni) || container.ContainsKey(pathToIni))
                {
                    return true;
                }
            }

            return false;
        }

        /// <summary>
        ///     EN: Set cache from container only if exist in this container
        /// </summary>
        /// <param name="pathToIni">Path to ini file</param>
        private void getCachedData(string pathToIni)
        {
            if (!pathToIni.Equals(nameCache))
            {
                lock (syncContainer)
                {
                    container.TryGetValue(pathToIni, out cache);
                }
            }
        }
    }
}