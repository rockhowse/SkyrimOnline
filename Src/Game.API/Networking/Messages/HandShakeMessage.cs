using Lidgren.Network;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Game.API.Networking.Messages
{
    public class HandShakeMessage
        : IGameMessage
    {
        public HandShakeMessage(NetIncomingMessage im)
        {
            this.Decode(im);
        }

        public HandShakeMessage()
        {
        }

        public GameMessageTypes MessageType
        {
            get
            {
                return GameMessageTypes.HandShake;
            }
        }

        public Int32 Version
        {
            get;
            set;
        }

        public string Username
        {
            get;
            set;
        }

        public void Decode(NetIncomingMessage im)
        {
            this.Version = im.ReadInt32();
            this.Username = im.ReadString();
        }

        public void Encode(NetOutgoingMessage om)
        {
            om.Write(this.Version);
            om.Write(this.Username);
        }
    }
}
