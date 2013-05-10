using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Game.API
{
    public interface IWorld
    {
        void Update();

        void OnEnter();
    }
}
