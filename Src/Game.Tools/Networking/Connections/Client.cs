using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Text;
using System.Threading.Tasks;

namespace Game.Tools.Networking.Connections
{
    public interface Client
    {
        /// <summary>
        /// When client start first and server not responding - client wait for server
        /// </summary>
        void ConnectListener(IPEndPoint server);

        /// <summary>
        /// I don't know right now, maybey messagelistener
        /// </summary>
        void Listener();
        
    }
}
