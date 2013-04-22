using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Lidgren.Network;

namespace Skyrim.API.Networking
{
    public interface IGameMessage
    {
        GameMessageTypes MessageType { get; }

        void Decode(NetIncomingMessage im);
        void Encode(NetOutgoingMessage om);

    }
}
