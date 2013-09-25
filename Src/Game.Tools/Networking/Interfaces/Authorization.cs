using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Game.Tools.Networking.Interfaces
{
    public interface Authorization
    {

        bool TryAutorize(ref Client client);


    }
}
