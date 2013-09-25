using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Game.Tools.Networking.Interfaces
{
    public interface SysInfo
    {
        string OS { get; }
        int CPU { get; }
        int[] Cores { get; }
        int[] maxThread { get; }
    }
}
