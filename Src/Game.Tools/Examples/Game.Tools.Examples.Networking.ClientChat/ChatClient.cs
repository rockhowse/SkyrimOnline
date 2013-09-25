
using Game.Tools.Networking.Connections;
using Game.Tools.Networking.Messages;
using Game.Tools.Networking.Messages.Interfaces;
using Game.Tools.Networking.Messages.Managment;
using Game.Tools.Networking.Messages.Templates;
using Game.Tools.Networking.Messages.Types;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace Game.Tools.Example.ClientChat
{
    public class ChatClient : TCPClient
    {

        private static Socket client;
        private static MessageCommunication ms;

        public ChatClient(IPEndPoint server)
        {
            Console.Title = "Example Chat Client";
            client = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.IP);
            ConnectListener(server);
            Listener();
        }

        public void ConnectListener(IPEndPoint server)
        {
            while ( !client.Connected )
            {
                try
                {
                    client.Connect(server);
                }
                catch ( SocketException e )
                {
                    Console.WriteLine("Can't reach server: " + server.Address + ":" + server.Port);
                }
                Thread.Sleep(100);
            }

            if(client.Connected) {
                Console.WriteLine("Connected to server: " + server.Address + ":" + server.Port);
            }

        }

        public void Disconnect()
        {
            throw new NotImplementedException();
        }

        public void Listener()
        {
            if ( client != null && client.Connected )
            {
                ms = new MessageCommunication(client);
                ChatManager cm = new ChatManager();
                Message message = null;
                TextMessage textMessage;

                // Message
                while ( client.Connected )
                {

                    // Sending message to Server
                    textMessage = cm.CreateTextMessage("Hello server");
                    Console.WriteLine("[Client] Client ---> Server | Sending message");
                    ms.Send(textMessage);

                    // Recive message from Server
                    message = ms.Recive();

                    if ( message != null )
                    {

                        Console.WriteLine("[Client] Server ---> Client | Recived message");
                        if ( message is TextMessage )
                        {
                            textMessage = ( TextMessage ) message;

                            TimeSpan MessageTime = new TimeSpan(textMessage.Date);
                            // Latency, message created to message recived
                            double latency = ( ( DateTime.Now.ToUniversalTime().Ticks - textMessage.Date ) / 10000 );

                            // if type of text message is ToAll
                            if ( textMessage.Type == TextMessageType.ToAll )
                            {
                                Console.WriteLine("MessageTime: " + MessageTime.Hours + ":" + MessageTime.Minutes + ":" + MessageTime.Seconds + " Latency: " + latency + "ms Message: " + textMessage.Text);
                            }

                        }
                    }


                    Thread.Sleep(1000);
                } // End of message
            }
            Console.Write("Lost connection to server, press any key to exit.");
            Console.Read();
        }

    }
}
