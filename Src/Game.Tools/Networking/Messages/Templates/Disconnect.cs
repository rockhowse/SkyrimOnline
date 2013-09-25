using Game.Tools.Networking.Messages.Interfaces;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Game.Tools.Networking.Messages.Templates
{
    [Serializable]
    public struct Disconnect : Command
    {

        public string reason;

    }
}
