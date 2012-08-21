//--------------------------------------------------------------------------------
/// @author Maxime GRIOT
//--------------------------------------------------------------------------------

using System;
using System.Collections.Generic;
using System.Linq;
using System.Windows.Forms;
using System.IO;
using System.Diagnostics;

namespace Updater
{
    static class Program
    {
        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main()
        {
            if (Application.ExecutablePath.EndsWith("SkyrimOnlineDuplicate.exe"))
            {
                Application.EnableVisualStyles();
                Application.SetCompatibleTextRenderingDefault(false);
                Application.Run(new Panel());
            }
            else
            {
                File.Delete("SkyrimOnlineDuplicate.exe");
                File.Copy(Application.ExecutablePath, "SkyrimOnlineDuplicate.exe");
                Process.Start("SkyrimOnlineDuplicate.exe");
                Application.Exit();
            }
        }
    }
}
