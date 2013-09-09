#region

using System;
using Lidgren.Network;

#endregion

namespace Game.API.Networking.Messages
{
    public class HandShakeMessage
        : IGameMessage
    {
        public HandShakeMessage(NetIncomingMessage im)
        {
            Decode(im);
        }

        public HandShakeMessage()
        {
        }

        public Int32 Version { get; set; }

        public string Username { get; set; }

        public GameMessageTypes MessageType
        {
            get { return GameMessageTypes.HandShake; }
        }

        public void Decode(NetIncomingMessage im)
        {
            Version = im.ReadInt32();
            Username = im.ReadString();
        }

        public void Encode(NetOutgoingMessage om)
        {
            om.Write(Version);
            om.Write(Username);
        }
    }
}