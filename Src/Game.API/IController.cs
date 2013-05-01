using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Game.API
{
    public abstract class IController
    {
#region Input
        abstract public void EnableInput();
        abstract public void DisableInput();
        abstract public bool IsMenuMode();
#endregion

#region Game
        abstract public void PlaceAtMe();
        abstract public IActor GetPlayer();
#endregion
    }
}
