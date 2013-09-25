using Game.Tools.Elements.Items;
using Game.Tools.Elements.Models;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Game.Tools.Elements
{
    interface Character : ModelInterface
    {
        string name { get; }
        string surname { get; }
        Character[] Comrades { get; }
        Type Type { get; }
        InventoryInterface Inventory { get; }

    }
}
