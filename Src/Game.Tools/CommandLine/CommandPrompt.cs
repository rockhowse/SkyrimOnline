#region

using System;
using System.Threading;
using Game.Tools.Language;
using System.Collections;
using Game.Tools.CommandLine.Interfaces;
using System.Text.RegularExpressions;

#endregion

namespace Game.Tools.CommandLine
{
    public class CommandPrompt
    {
        private static Thread console;
        private static volatile CommandPrompt instance;
        private static readonly object syncRoot = new Object();
        private static readonly object syncCommand = new Object();
        private static readonly object syncEvent = new Object();
        private static readonly object syncPrint = new Object();
        private static volatile ArrayList commandsList = new ArrayList();


        // Maximum and minimum cursor positions (start to end)
        private static readonly int minXY = 0, maxX = Console.WindowWidth - 1, maxY = Console.WindowHeight - 1;

        // Info Line cursor positions (start to end)
        private static readonly int[ , ] infoLinePos = new int[ 2, 2 ] { { minXY, minXY }, { maxX, minXY } };

        // Event Line cursor positions (start to end)
        private static readonly int[ , ] eventLinePos = new int[ 2, 2 ] { { infoLinePos[ 0, 0 ], infoLinePos[ 0, 1 ] + 1 }, { infoLinePos[ 1, 0 ], infoLinePos[ 1, 1 ] + 1 } };

        // Command Line cursor positions (start to end)
        private static readonly int[ , ] commandPos = new int[ 2, 2 ] { { minXY, maxY }, { maxX, maxY } };

        // Prompt Line cursor positions (start to end)
        private static readonly int[ , ] promptPos = new int[ 2, 2 ] { { eventLinePos[ 0, 0 ], eventLinePos[ 0, 1 ] + 1 }, { commandPos[ 0, 0 ], commandPos[ 0, 1 ] - 2 } };

        // Alphabetic array
        private static readonly char[] charts = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z' };

        // Temp text printed on prompt area
        private static readonly ArrayList textList = new ArrayList();

        private CommandPrompt()
        {
        }

        private CommandPrompt(string title)
        {
            if ( console == null )
            {
                console = new Thread(Listener);
                console.Start(title);
            }
        }

        public static CommandPrompt CreateInstance(string title)
        {
            if ( instance == null )
            {
                lock ( syncRoot )
                {
                    if ( instance == null ) instance = new CommandPrompt(title);
                }
            }

            return instance;
        }

        public static CommandPrompt getInstance()
        {
            return instance;
        }

        /// <summary>
        /// Add commadn to commands list
        /// </summary>
        /// <param name="command">Command to remove</param>
        public void AddCommand(Command command)
        {
            if ( command != null )
            {
                lock ( syncCommand )
                {
                    commandsList.Add(command);
                }
            }
        }

        /// <summary>
        /// Remove command from commands list
        /// </summary>
        /// <param name="command">Command to remove</param>
        public void RemoveCommand(Command command)
        {
            if ( command != null )
            {
                lock ( syncCommand )
                {
                    commandsList.Remove(command);
                }
            }
        }

        /// <summary>
        /// Get Command from List, used only for test
        /// </summary>
        /// <param name="index">Command index</param>
        /// <returns>Command object</returns>
        public Command GetCommand(int index) 
        {

            lock ( syncCommand )
            {
                if ( commandsList.Count > 0 && index > -1 && index < commandsList.Count )
                {
                    return (Command) commandsList[ index ];
                }
            }

            return null;
        }


        /// <summary>
        /// Configurate when start
        /// </summary>
        /// <param name="title">Title of cmd</param>
        private void OnStartUp(string title)
        {
            Console.BufferHeight = Console.WindowHeight;
            Console.BufferWidth = Console.WindowWidth;
            Console.Title = title;
        }

        /// <summary>
        /// Repainting cmd screen
        /// </summary>
        private void RePaint()
        {
            Console.Clear();
            InfoLine("This is a test version of CommandLine");
            SetClear();
            EventLine("");
            SetClear();
        }

        /// <summary>
        /// Set stanard colors in cmd
        /// </summary>
        private void SetClear()
        {
            Console.ForegroundColor = ConsoleColor.Gray;
            Console.BackgroundColor = ConsoleColor.Black;
        }

        /// <summary>
        /// Set Info in first line
        /// </summary>
        /// <param name="info">Info like string</param>
        private void InfoLine(string info)
        {
            Console.ForegroundColor = ConsoleColor.Black;
            Console.BackgroundColor = ConsoleColor.White;
            Console.SetCursorPosition(infoLinePos[ 0, 0 ], infoLinePos[ 0, 1 ]);
            Console.Write("Info: " + info);

            for ( int pos = Console.CursorLeft; pos < maxX + 1; pos++ )
            {
                Console.Write(" ");
            }

        }

        /// <summary>
        /// Set Event in sec line
        /// </summary>
        /// <param name="info">Info like string</param>
        public void EventLine(string info)
        {
            lock ( syncEvent )
            {
                Console.ForegroundColor = ConsoleColor.Green;
                Console.BackgroundColor = ConsoleColor.DarkCyan;
                Console.SetCursorPosition(eventLinePos[ 0, 0 ], eventLinePos[ 0, 1 ]);
                Console.Write("Event: " + info);

                for ( int pos = Console.CursorLeft; pos < maxX + 1; pos++ )
                {
                    Console.Write(" ");
                }
            }
        }

        /// <summary>
        /// Using when writing commands TODO
        /// </summary>
        /// <returns>Command like string</returns>
        private string Command()
        {
            Console.SetCursorPosition(commandPos[ 0, 0 ], commandPos[ 0, 1 ]);
            Console.Write("Command: ");
            Regex r = new Regex("[A-Za-z0-9]");
            ConsoleKeyInfo key;
            string command = "";

            while ( ( key = Console.ReadKey() ).Key != ConsoleKey.Enter )
            {

                if ( key.Key.Equals(ConsoleKey.Backspace) )
                {
                    if ( command != null && command.Length > 0 )
                    {
                        command = command.Remove(command.Length - 1);
                    }
                }

                if ( r.IsMatch("" + key.KeyChar) )
                {
                    command += Char.ToLower(key.KeyChar);
                }

            }

            return command;
        }

        /// <summary>
        /// Output text in to the console in specific area
        /// </summary>
        /// <param name="str">String to print</param>
        public void Print(string str)
        {
            lock ( syncPrint )
            {
                if ( str != null && !str.Equals("") && !str.Equals(" ") )
                {

                    if ( str.Length > maxX )
                    {
                        foreach ( string line in TextWrapping(str) )
                        {
                            textList.Add(line);
                        }
                    }
                    else
                    {
                        textList.Add(str);
                    }
                    // Adding string to list


                    // Check and set cursor position
                    if ( !checkCursorPosition(promptPos[ 0, 0 ], promptPos[ 0, 1 ], promptPos[ 1, 0 ], promptPos[ 1, 1 ]) )
                    {
                        Console.SetCursorPosition(promptPos[ 0, 0 ], promptPos[ 0, 1 ]);
                    }

                    int position = 0;

                    if ( textList.Count > maxY )
                    {
                        position = textList.Count - promptPos[ 1, 1 ];
                    }

                    for ( ; position < textList.Count; position++ )
                    {
                        Console.Write(textList[ position ]);
                    }

                }
            }

        }

        /// <summary>
        /// Check cursor current position in selected area
        /// </summary>
        /// <param name="startX">Starting point X selected area</param>
        /// <param name="startY">Starting point Y selected area</param>
        /// <param name="endX">End point X selected area</param>
        /// <param name="endY">End point Y selected area</param>
        /// <returns>true if cursor is on selected area, otherwise false</returns>
        private static bool checkCursorPosition(int startX, int startY, int endX, int endY)
        {

            int cursorX = Console.CursorLeft;
            int cursorY = Console.CursorTop;

            if ( cursorX >= startX && cursorX <= endX && cursorY >= startY && cursorY <= endY )
            {
                return true;
            }

            return false;
        }

        /// <summary>
        /// Creates a substring of the string and adds to an array
        /// </summary>
        /// <param name="str">String to wrap</param>
        /// <returns>Null if str is null, othervise array</returns>
        private static string[] TextWrapping(string str)
        {
            if ( str != null )
            {
                // how many lines
                int max = ( int ) Math.Ceiling(( double ) str.Length / maxX);
                string[] array = new string[ max ];
                string sub = null;

                for ( int i = 0; i < max; i++ )
                {
                    if ( str.Length > maxX )
                    {
                        sub = str.Substring(0, maxX);
                        str = str.Remove(0, maxX);
                    }
                    else sub = str;
                    array[ i ] = sub;
                }
                return array;
            }
            return null;
        }

        /// <summary>
        /// Command listener
        /// </summary>
        /// <param name="title">Title like string</param>
        private void Listener(object title)
        {
            if ( title is string )
            {

                OnStartUp( (string) title);
                while ( true )
                {

                    RePaint();

                    foreach ( Command command in commandsList )
                    {
                        command.onExecute(Command());
                    }
                    Thread.Sleep(300);
                }
            }
        }

        

        

    }
}