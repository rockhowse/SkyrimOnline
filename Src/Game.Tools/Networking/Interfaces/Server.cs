using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Text;
using System.Threading.Tasks;

namespace Game.Tools.Networking.Interfaces
{
    public interface Server
    {

        void Setup(IPAddress address, int port);
        void Listener();
        void GetClient(string id);

        void OnServerStarted();
        void OnServerStoped();
        void OnServerClose();

        void OnClientConnect(Client client);
        void OnClientDicconnect(Client client);
        void OnClientDroped(Client client);

    }
}
