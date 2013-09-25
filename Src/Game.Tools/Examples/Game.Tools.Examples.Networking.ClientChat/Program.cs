using Game.Tools.Example.ClientChat;
using System;
using System.Net;

namespace Game.Tools.Examples.Networking.ClientChat
{
    class Program
    {
        static void Main(string[] args)
        {
            ChatClient chat = new ChatClient(new IPEndPoint(IPAddress.Loopback, 8001));
        }
    }
}
