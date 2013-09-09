#region

using System;
using System.Collections.Generic;
using System.IO;

#endregion

namespace Game.MasterServer
{
    public class ServerManager
    {
        private readonly List<Guid> guids = new List<Guid>();
        private readonly Dictionary<Int64, Guid> registeredGuids = new Dictionary<Int64, Guid>();

        public ServerManager()
        {
            LoadGuids();
            CreateFileWatcher(".");
        }

        private void LoadGuids()
        {
            lock (this)
            {
                while (true)
                {
                    try
                    {
                        string line;
                        StreamReader file = new StreamReader("master.server.guid.txt");
                        while ((line = file.ReadLine()) != null)
                        {
                            try
                            {
                                if (!registeredGuids.ContainsValue(new Guid(line)) && !guids.Contains(new Guid(line)))
                                    guids.Add(new Guid(line));
                            }
                            catch
                            {
                            }
                        }

                        Console.WriteLine("Reloaded GUIDs {0} are free", guids.Count);

                        file.Close();

                        return;
                    }
                    catch
                    {
                    }
                }
            }
        }

        public bool Register(Int64 id, Guid guid)
        {
            lock (this)
            {
                if (guids.Contains(guid))
                {
                    registeredGuids.Add(id, guid);
                    guids.Remove(guid);
                    return true;
                }
                if (registeredGuids.ContainsKey(id))
                    return true;
            }
            return false;
        }

        public void Release(Int64 id)
        {
            lock (this)
            {
                Guid guid;
                if (registeredGuids.TryGetValue(id, out guid))
                {
                    registeredGuids.Remove(id);
                    guids.Add(guid);
                }
            }
        }

        public void CreateFileWatcher(string path)
        {
            // Create a new FileSystemWatcher and set its properties.
            FileSystemWatcher watcher = new FileSystemWatcher();
            watcher.Path = path;
            /* Watch for changes in LastAccess and LastWrite times, and 
               the renaming of files or directories. */
            watcher.NotifyFilter = NotifyFilters.LastAccess | NotifyFilters.LastWrite
                                   | NotifyFilters.FileName | NotifyFilters.DirectoryName;

            // Add event handlers.
            watcher.Changed += OnChanged;
            watcher.Created += OnChanged;
            watcher.Deleted += OnChanged;
            watcher.Filter = "master.server.guid.txt";

            // Begin watching.
            watcher.EnableRaisingEvents = true;
        }

        // Define the event handlers.
        private void OnChanged(object source, FileSystemEventArgs e)
        {
            LoadGuids();
        }
    }
}