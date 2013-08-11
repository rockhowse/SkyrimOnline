using Lidgren.Network;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Game.API.Networking.Messages;

namespace Game.API.Networking
{
    public class PacketHandler
    {
        public delegate void PacketHandlerDelegate(IGameMessage message);

        public event PacketHandlerDelegate OnChatTalk;
        public event PacketHandlerDelegate OnUpdatePlayerState;

        public void Handle(NetIncomingMessage inc)
        {
            try
            {
                var gameMessageType = (GameMessageTypes)inc.ReadByte();
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
