using Game.Tools.Networking.Connections;
using Game.Tools.Networking.Messages;
using Game.Tools.Networking.Messages.Interfaces;
using Game.Tools.Networking.Messages.Managment;
using Game.Tools.Networking.Messages.Templates;
using Game.Tools.Networking.Messages.Types;
using System;
using System.Net;
using System.Net.Sockets;

namespace Game.Tools.Example.ServerChat
{
    public class ChatServer : TCPServer
    {

        private static Socket server;
        private static Socket client;
        private static bool stop = false;

        public ChatServer(EndPoint ServerPoint)
        {
            Console.Title = "Example Chat Server";
            server = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.IP);
            server.Bind(ServerPoint);
            server.Listen(1);
            Console.WriteLine("Server started at: " + ( ( IPEndPoint ) ServerPoint ).Address + ":" + ( ( IPEndPoint ) ServerPoint ).Port);
            Listener();
        }

        public Socket ServerSocket
        {
            get { return server; }
        }

        public EndPoint ServerEndPoint
        {
            get { throw new NotImplementedException(); }
        }

        public void Listener()
        {
            if ( server != null )
            {
                while ( !stop )
                {
                    client = server.Accept();
                    Console.WriteLine("Client connected from: " + ( ( IPEndPoint ) client.RemoteEndPoint ).Address + ":" + ( ( IPEndPoint ) client.RemoteEndPoint ).Port);
                    /* Message chat system only for one client implementation */

                    MessageCommunication ms = new MessageCommunication(client);
                    ChatManager cm = new ChatManager();
                    Message message = null;
                    TextMessage textMessage;

                    // Message 
                    while ( client.Connected )
                    {

                        message = ms.Recive();
                        if ( message != null )
                        {
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


                        // Sending message to Server
                        textMessage = cm.CreateTextMessage("Hello client");
                        Console.WriteLine("[Server] Server ---> Client | Sending message");
                        ms.Send(textMessage);

                    } // End of message
                    Console.WriteLine("Client: " + ( ( IPEndPoint ) client.RemoteEndPoint ).Address + ":" + ( ( IPEndPoint ) client.RemoteEndPoint ).Port + " disconnected");
                    /* ... */
                }
            }
        }

        public void Stop()
        {
            stop = true;
        }
    }
}
