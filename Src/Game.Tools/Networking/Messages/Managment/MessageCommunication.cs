using Game.Tools.Networking.Messages.Interfaces;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Runtime.Serialization;
using System.Runtime.Serialization.Formatters.Binary;
using System.Security;
using System.Text;
using System.Threading.Tasks;

namespace Game.Tools.Networking.Messages
{
    public class MessageCommunication
    {
        private Socket socket;
        private UdpClient client;

        public MessageCommunication(Socket socket)
        {
            this.socket = socket;
        }

        public MessageCommunication(UdpClient client)
        {
            this.client = client;
        }

        /// <summary>
        /// TCP
        /// </summary>
        /// <returns></returns>
        public Message Recive()
        {
            byte[] buffer = new byte[ socket.ReceiveBufferSize ];
            int recivdBytes = 0;

            try
            {
                recivdBytes = socket.Receive(buffer);
            }
            catch ( Exception e )
            {
                if ( e is ArgumentNullException ) Console.WriteLine("Argument null exception: " + e.Message);
                if ( e is SocketException ) Console.WriteLine("Socket exception: " + e.Message);
                if ( e is ObjectDisposedException ) Console.WriteLine("Object disposed exception: " + e.Message);
                if ( e is SecurityException ) Console.WriteLine("Security exception: " + e.Message);
            }

            return Deserialize(buffer);
        }

        /// <summary>
        /// Client UDP
        /// </summary>
        /// <param name="sender"></param>
        /// <returns></returns>
        public Message Recive(ref IPEndPoint server)
        {
            byte[] buffer = null;

            try
            {
                buffer = client.Receive(ref server);
            }
            catch ( Exception e )
            {
                Console.WriteLine(e.ToString());
            }

            return Deserialize(buffer);
        }

        /// <summary>
        /// Server UDP
        /// </summary>
        /// <param name="sender"></param>
        /// <returns></returns>
        public Message ReciveFrom(ref EndPoint client)
        {
            byte[] buffer = new byte[ 1024 ];
            int recivdBytes = 0;
            try
            {
                recivdBytes = socket.ReceiveFrom(buffer, ref client);
            }
            catch ( Exception e )
            {
            }
            return Deserialize(buffer);
        }

        /// <summary>
        /// TCP Send
        /// </summary>
        /// <param name="message">Message object</param>
        public void Send(Message message)
        {

            byte[] buffer = null;
            int byteSended = 0;

            buffer = Serialize(message);

            try
            {
                byteSended = socket.Send(buffer, buffer.Length, SocketFlags.None);
            }
            catch ( Exception e )
            {
                if ( e is SocketException ) Console.WriteLine("Socket exception: " + e.Message);

                if ( e is ObjectDisposedException ) Console.WriteLine("Object disposed exception: " + e.Message);

                if ( e is ArgumentNullException ) Console.WriteLine("Argument null exception: " + e.Message);

                if ( e is ArgumentOutOfRangeException ) Console.WriteLine("Argument out of range exception: " + e.Message);
            }
        }

        /// <summary>
        /// UDP Client
        /// </summary>
        /// <param name="message"></param>
        /// <param name="receaver"></param>
        public void Send(Message message, IPEndPoint server)
        {

            byte[] buffer = null;
            int byteSended = 0;

            try
            {
                buffer = Serialize(message);
                while ( byteSended != buffer.Length )
                {
                    byteSended = client.Send(buffer, buffer.Length, server);
                }
            }
            catch ( Exception e )
            {
                Console.WriteLine(e.ToString());
            }

        }

        /// <summary>
        /// UDP Server
        /// </summary>
        /// <param name="message"></param>
        /// <param name="receaver"></param>
        public void SendTo(Message message, ref EndPoint client)
        {
            byte[] buffer = null;
            int byteSended = 0;

            try
            {
                buffer = Serialize(message);
                while ( byteSended != buffer.Length )
                {
                    byteSended = socket.SendTo(buffer, buffer.Length, SocketFlags.None, client);
                }
            }
            catch ( Exception e )
            {
                Console.WriteLine(e.ToString());
            }
        }

        private Message Deserialize(byte[] byteMessage)
        {
            Message message = null;
            MemoryStream ms = new MemoryStream();
            ms.Write(byteMessage, 0, byteMessage.Length);
            ms.Position = 0;
            BinaryFormatter formatter = new BinaryFormatter();
            try
            {
                message = ( Message ) formatter.Deserialize(ms);
            }
            catch ( Exception e )
            {
                if ( e is ArgumentNullException ) Console.WriteLine("Argument null exception: " + e.Message);
                if ( e is SerializationException ) Console.WriteLine("Serialization exception: " + e.Message);
                if ( e is SecurityException ) Console.WriteLine("Security exception: " + e.Message);
            }

            return message;

        }

        private byte[] Serialize(Message message)
        {
            MemoryStream ms = new MemoryStream();
            BinaryFormatter formatter = new BinaryFormatter();
            formatter.Serialize(ms, message);
            return ms.ToArray();
        }

    }
}
