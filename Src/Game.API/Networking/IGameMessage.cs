#region

using Lidgren.Network;

#endregion

namespace Game.API.Networking
{
    public interface IGameMessage
    {
        GameMessageTypes MessageType { get; }

        void Decode(NetIncomingMessage im);
        void Encode(NetOutgoingMessage om);
    }
}