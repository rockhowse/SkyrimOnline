using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Game.Tools.CommandLine.Interfaces
{
    public interface Command
    {
        
        string command { get; }
        string description { get; }
        void onExecute(string str);

    }
}
