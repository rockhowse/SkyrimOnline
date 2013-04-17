using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Skyrim.API
{
    public static class MasterServer
    {
        public const int MasterServerPort = 14343;
        public const int GameServerPort = 14242;
    }

    public enum MasterServerMessageType
    {
        RegisterHost,
        RequestHostList,
        RequestIntroduction,
    }
}
