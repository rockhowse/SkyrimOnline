using Game.Tools.Networking.Messages.Templates;
using Game.Tools.Networking.Messages.Types;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Game.Tools.Networking.Messages.Managment
{
    public class ChatManager
    {

        public ChatManager() { }

        /// <summary>
        /// Create one to world (all receivers) text message
        /// </summary>
        /// <param name="text">Some text</param>
        /// <returns>Created message</returns>
        public TextMessage CreateTextMessage(string text)
        {
            TextMessage message = new TextMessage();
            message.Type = TextMessageType.ToAll;
            message.Text = text;
            message.Date = getTicks();
            return message;
        }

        /// <summary>
        /// Create one to one text message
        /// </summary>
        /// <param name="text">Some text</param>
        /// <param name="receiver">Receiver</param>
        /// <returns>Created message</returns>
        public TextMessage CreateTextMessage(string text, string receiver)
        {
            TextMessage message = new TextMessage();
            message.Type = TextMessageType.ToReciver;
            message.Receiver = receiver;
            message.Text = text;
            message.Date = getTicks();
            return message;
        }

        /// <summary>
        /// Create multi receivers group message
        /// </summary>
        /// <param name="text">Some text</param>
        /// <param name="receivers">Gropu of receivers</param>
        /// <returns>Created message</returns>
        public TextMessage CreateTextMessage(string text, List<string> receivers)
        {
            TextMessage message = new TextMessage();
            message.Type = TextMessageType.ToGroup;
            message.Receivers = receivers;
            message.Text = text;
            message.Date = getTicks();
            return message;
        }

        /// <summary>
        /// Return current date in ticks
        /// </summary>
        /// <returns>Ticks as long</returns>
        private long getTicks() 
        {
            return DateTime.Now.ToUniversalTime().Ticks;
        }

    }
}
