using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Game.Tools.Networking.Interfaces
{
    public interface ClientQueue
    {

        List<Client> ClientList { get; }

        void AddClient(Client client);
        void RemoveClient(Client client);


    }
}
