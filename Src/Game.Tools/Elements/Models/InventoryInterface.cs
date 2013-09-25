using Game.Tools.Elements.Items;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Game.Tools.Elements.Models
{
    interface InventoryInterface
    {
        
        Dictionary<short, Item>  items { get; }
        void AddItem(short id);
        void RemoveItem(short id);
        
    }
}
