#region

using Game.API.Networking.Messages;
using Lidgren.Network;

#endregion

namespace Game.API.Networking
{
    public class PacketHandler
    {
        public delegate void PacketHandlerDelegate(IGameMessage message);

        public static int PROTOCOL_VERSION = 1;

        public event PacketHandlerDelegate OnChatTalk;
        public event PacketHandlerDelegate OnUpdatePlayerState;

        public void Handle(NetIncomingMessage inc)
        {
            try
            {
                var gameMessageType = (GameMessageTypes) inc.ReadByte();
                switch (gameMessageType)
                {
                    case GameMessageTypes.UpdatePlayerState:
                        OnUpdatePlayerState(new UpdatePlayerStateMessage(inc));
                        break;
                    case GameMessageTypes.ChatTalk:
                        OnChatTalk(new ChatTalkMessage(inc));
                        break;
                }
            }
            catch
            {
            }
        }
    }
}