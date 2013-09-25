using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Game.Tools.Networking.Messages.Types
{
    public struct TextMessageType
    {
        /// <summary>
        /// Message to all on server, like "message to world chat"
        /// </summary>
        public static readonly short ToAll = 0;

        /// <summary>
        /// Message Type: only to one reciver, like "wisper to..."
        /// </summary>
        public static readonly short ToReciver = 1;

        /// <summary>
        /// Message type: only to selected group, like "message to party group"
        /// </summary>
        public static readonly short ToGroup = 2;
    }
}
