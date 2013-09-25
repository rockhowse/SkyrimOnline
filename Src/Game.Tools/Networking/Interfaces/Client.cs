using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Text;
using System.Threading.Tasks;

namespace Game.Tools.Networking.Interfaces
{
    public interface Client
    {
        string name { get; }
        string password { get; }
        string id { get; }
    }
}
