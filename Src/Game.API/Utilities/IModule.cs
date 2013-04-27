using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Game.API.Utilities
{
    public enum GameType
    {
        kSkyrim,
        kOblivion
    }

    public interface IModule
    {
        string Name
        {
            get;
        }

        GameType GameType
        {
            get;
        }
    }
}
