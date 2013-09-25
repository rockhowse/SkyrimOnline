using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading.Tasks;

namespace Game.Tools.Networking.Connections
{
    public interface Server
    {

        Socket ServerSocket { get; }
        EndPoint ServerEndPoint { get; }
        void Listener();
        void Stop();

    }
}
