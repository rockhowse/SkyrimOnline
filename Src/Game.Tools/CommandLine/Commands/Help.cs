using Game.Tools.CommandLine.Interfaces;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Game.Tools.CommandLine.Commands
{
    internal class Help : Command
    {

        private CommandPrompt cmp = CommandPrompt.getInstance();

        public Help() { cmp.AddCommand(this); }

        public string command
        {
            get { return "help"; }
        }

        public string description
        {
            get { return "Help description"; }
        }

        public void onExecute(string str)
        {
            if ( str != null && str.Equals(str) )
            {
                /* TODO */
            }
        }

    }
}
