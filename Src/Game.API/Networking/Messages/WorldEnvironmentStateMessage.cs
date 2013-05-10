using Lidgren.Network;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Game.API.Networking.Messages
{
    public class WorldEnvironmentStateMessage
        : IGameMessage
    {

        public enum MessageSignature : byte
        {
            kPlayer,
            kServer,
            kSystem
        }

        public WorldEnvironmentStateMessage(NetIncomingMessage im)
        {
            this.Decode(im);
        }

        public WorldEnvironmentStateMessage()
        {
        }

        public WorldEnvironmentStateMessage(string message)
        {
            this.Message = message;
        }

        public GameMessageTypes MessageType
        {
            get
            {
                return GameMessageTypes.WorldEnvironmentState;
            }
        }

        public void Decode(NetIncomingMessage im)
        {
            this.Message = im.ReadString();
            this.Signature = (MessageSignature)im.ReadByte();
        }

        public void Encode(NetOutgoingMessage om)
        {
            om.Write(this.Message);
            om.Write((byte)this.Signature);
        }
    }
}
