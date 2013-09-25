using Game.Tools.Networking.Messages.Interfaces;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Game.Tools.Networking.Messages.Templates
{
    [Serializable]
    public struct TextMessage : Message
    {
        private long ticks;
        private short type;
        private string text;
        private string receiver;
        private List<string> receivers;
        private string sender;

        /// <summary>
        /// Message type like TextMessageType
        /// </summary>
        public short Type { get { return type; } set { type = value; } }

        /// <summary>
        /// Some text to send
        /// </summary>
        public string Text { get { return text; } set { text = value; } }

        /// <summary>
        /// Who send text message
        /// </summary>
        public string Sender { get { return sender; } set { sender = value; } }

        /// <summary>
        /// Who receive text message
        /// </summary>
        public string Receiver { get { return receiver; } set { receiver = value; } }

        /// <summary>
        /// List of multiple receivers
        /// </summary>
        public List<string> Receivers { get { return receivers; } set { receivers = value; } }

        /// <summary>
        /// Date when text message was created, like tick
        /// </summary>
        public long Date { get { return ticks; } set { ticks = value; } }

    }
}
