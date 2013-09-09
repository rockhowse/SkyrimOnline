using Game.Tools.IniManager;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Game.Tools.Language
{

    public delegate void EventHandler();

    public class LanguageManager
    {

        //Events
        private event EventHandler Load;
        private event EventHandler Reload;
        private event EventHandler Change;

        private static volatile LanguageManager instance;
        private static object syncRoot = new Object();
        private static IniLoader serverConfig = null;
        private static IniLoader languageFile = null;


        /// <summary>
        /// EN: Loading GameServer.ini
        /// </summary>
        private LanguageManager()
        {
            //serverConfig = new IniLoader("GameServer.ini");
            Load();
            /* ... */
        }

        public static LanguageManager Instance
        {
            get
            {
                if (instance == null)
                {
                    lock (syncRoot)
                    {
                        if (instance == null)
                            instance = new LanguageManager();
                    }
                }

                return instance;
            }
        }

        /// <summary>
        /// Reloading language from config file
        /// </summary>
        public void ReloadLanguage(){
            //language = serverConfig.GetValue("General", "Language", Languages.LANGUAGE_ENGLISH);
            Reload();
        }

        /// <summary>
        /// Changing language
        /// </summary>
        public void ChangeLanguage()
        {

        }

        /// <summary>
        /// When language reloaded
        /// </summary>
        /// <param name="e"></param>
        protected virtual void onReload(EventArgs e)
        {
            if (Reload != null)
            {
                Reload();
            }
        }

        /// <summary>
        /// EN: When server config loaded
        /// </summary>
        /// <param name="e"></param>
        protected virtual void onLoadConfig(EventArgs e)
        {
            if (Load != null)
            {
                Load();
            }
        }

        /// <summary>
        /// EN: When Language changed
        /// </summary>
        /// <param name="e"></param>
        protected virtual void onLanguageChanged(EventArgs e)
        {
            if (Change != null)
            {
                Change();
            }
        }

    }

    public class Languages
    {
        public static readonly string LANGUAGE_ENGLISH = "English";
        public static readonly string ID_EN = "EN";

        public static readonly string LANGUAGE_POLISH = "Polish";
        public static readonly string ID_PL = "PL";
    }

}
