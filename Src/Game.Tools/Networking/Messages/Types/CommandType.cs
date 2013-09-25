using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Game.Tools.Networking.Messages.Types
{
    
    public struct CommandType
    {
        public static readonly short Admin = 0;
        public static readonly short Moderator = 1;
        public static readonly short Player = 2;
    }

}
