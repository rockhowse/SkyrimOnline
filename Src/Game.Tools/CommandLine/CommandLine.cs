using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace Game.Tools.CommandLine
{
    public class CommandPrompt
    {
        private static Thread console;
        private static volatile CommandPrompt instance;
        private static object syncRoot = new Object();

        private CommandPrompt()
        {
            console = new Thread(startListen);
        }

        public static CommandPrompt Instance
        {
            get
            {
                if (instance == null)
                {
                    lock (syncRoot)
                    {
                        if (instance == null)
                        {
                            instance = new CommandPrompt();
                            console.Start();
                        }
                    }
                }
                return instance;
            }
        }

        private void startListen()
        {

            string[] command = null;

            while (true)
            {
                command = Console.ReadLine().ToLower().Split(' ');

                if (command != null && command.Length > 0)
                {

                    // single command like "help"
                    if (command.Length == 1)
                    {
                        if (command[0].Equals(Commands.COMMAND_EXIT))
                        {
                            Environment.Exit(0);
                        }

                        if (command[0].Equals(Commands.COMMAND_HELP))
                        {
                            Console.WriteLine("Display Help");
                            Console.WriteLine("Command List:");
                            Console.WriteLine(Commands.DESCRIPTION_EXIT);
                            /* ... */
                        }
                    }
                    // command with one or more arguments like "reload lang"
                    else
                    {
                        // for reload section
                        if(command[0].Equals(Commands.COMMAND_RELOAD)) {
                            
                            if(command[1].Equals(Commands.COMMAND_RELOAD_LANGUAGE)) {
                                Language.LanguageManager lang = Language.LanguageManager.Instance;
                                lang.ReloadLanguage();
                            }

                        }

                    }

                    

                    if (command.Equals(Commands.COMMAND_RELOAD_LANGUAGE))
                    {

                    }

                }

                Thread.Sleep(300);
            }

        }

    }

    

}
