using Game.API.Networking;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Game.API.Networking.Messages;

namespace Game.Client.IO
{
    public partial class GameClient
    {
        private void HandleChatTalkMessage(IGameMessage msg)
        {
            ChatTalkMessage message = (ChatTalkMessage)msg;
            Entry.UserInterace.Chat.Log(message.Message);
        }

        private void HandleUpdatePlayerStateMessage(IGameMessage msg)
        {
            /* var message = new UpdatePlayerStateMessage(im);

             var timeDelay = (float)(NetTime.Now - im.SenderConnection.GetLocalTime(message.MessageTime));

             Player player = this.playerManager.GetPlayer(message.Id)
                             ??
                             this.playerManager.AddPlayer(
                                 message.Id, message.Position, message.Velocity, message.Rotation, false);

             player.EnableSmoothing = true;

             if (player.LastUpdateTime < message.MessageTime)
             {
                 player.SimulationState.Position = message.Position += message.Velocity * timeDelay;
                 player.SimulationState.Velocity = message.Velocity;
                 player.SimulationState.Rotation = message.Rotation;

                 player.LastUpdateTime = message.MessageTime;
             }*/
        }
    }
}
