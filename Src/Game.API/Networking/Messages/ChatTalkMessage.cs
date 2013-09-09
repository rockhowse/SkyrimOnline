#region

using Lidgren.Network;

#endregion

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
            Decode(im);
        }

        public ChatTalkMessage()
        {
        }

        public ChatTalkMessage(string message)
        {
            Message = message;
        }

        public string Message { get; set; }

        public MessageSignature Signature { get; set; }

        public GameMessageTypes MessageType
        {
            get { return GameMessageTypes.ChatTalk; }
        }

        public void Decode(NetIncomingMessage im)
        {
            Message = im.ReadString();
            Signature = (MessageSignature) im.ReadByte();
        }

        public void Encode(NetOutgoingMessage om)
        {
            om.Write(Message);
            om.Write((byte) Signature);
        }
    }
}