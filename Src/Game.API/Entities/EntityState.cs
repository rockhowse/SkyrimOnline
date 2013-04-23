using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Microsoft.Xna.Framework;

namespace Game.API.Entities
{
    public class EntityState : ICloneable
    {
        private float rotation;

        public Vector3 Position { get; set; }

        public float Rotation
        {
            get
            {
                return this.rotation;
            }

            set
            {
                if (this.rotation == value % MathHelper.TwoPi)
                {
                    return;
                }

                this.rotation = value % MathHelper.TwoPi;
            }
        }

        public Vector3 Velocity { get; set; }

        public object Clone()
        {
            return new EntityState { Position = this.Position, Rotation = this.Rotation, Velocity = this.Velocity };
        }
    }
}
