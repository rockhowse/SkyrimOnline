using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Text;
using System.Threading.Tasks;

namespace Game.Tools.Networking.Connections
{
    public interface UDPServer : Server
    {

        EndPoint ClientEndPoint { get; }

    }
}
