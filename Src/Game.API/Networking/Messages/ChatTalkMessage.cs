using Lidgren.Network;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Game.API.Networking.Messages
{
    public class ChatTalkMessage
        : IGameMessage
    {

        public enum MessageSignature : byte
        {
            kPlayer,
            kServer,
            kSystem
        }

        public ChatTalkMessage(NetIncomingMessage im)
        {
            this.Decode(im);
        }

        public ChatTalkMessage()
        {
        }

        public ChatTalkMessage(string message)
        {
            this.Message = message;
        }

        public GameMessageTypes MessageType
        {
            get
            {
                return GameMessageTypes.ChatTalk;
            }
        }

        public string Message
        {
            get;
            set;
        }

        public MessageSignature Signature
        {
            get;
            set;
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
