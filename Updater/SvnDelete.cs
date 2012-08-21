using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;

namespace Updater
{
    class SvnDelete
    {
        const string Dot = ".";
        const string Underscore = "_";


        private const string _svnFolderPrefix = Dot;
        private const string _svnFolderName = _svnFolderPrefix + "svn";

        public static void findSvnDirectories(string sDir)
        {
            try
            {
                foreach (string d in Directory.GetDirectories(sDir))
                {
                    findSvnDirectories(d);

                    if (d.EndsWith(".svn"))
                    {
                        System.Console.WriteLine(d);
                        deleteDirectory(d);
                    }
                }
            }
            catch (System.Exception ex)
            {
                Console.WriteLine(ex.Message);
            }
        }


        static void deleteDirectory(string path)
        {

            try
            {
                string[] files = Directory.GetFiles(path);
                string[] dirs = Directory.GetDirectories(path);

                //first del all the files in this dir
                foreach (string f in files)
                {
                    FileInfo info = new FileInfo(f);
                    info.Attributes = FileAttributes.Normal;//necessary to gain access for the file delete
                    File.Delete(f);
                }

                //Delte all of the nested directories - via recursive call
                foreach (string dirName in dirs)
                {
                    deleteDirectory(dirName);
                }

                //Finally - after deletinging all files and directories- del the .svn directory
                Directory.Delete(path);
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
            }

        }

    }
}
