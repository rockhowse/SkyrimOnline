using Game.Tools.Example.ServerChat;
using System;
using System.Net;

namespace Game.Tools.Examples.Networking.ServerChat
{
    class Program
    {
        static void Main(string[] args)
        {
            new ChatServer(new IPEndPoint(IPAddress.Loopback, 8001));
        }
    }
}
