#region

using System;
using Microsoft.Xna.Framework;

#endregion

namespace Game.API.Entities
{
    public class EntityState : ICloneable
    {
        private float rotation;

        public Vector3 Position { get; set; }

        public float Rotation
        {
            get { return rotation; }

            set
            {
                if (rotation == value%MathHelper.TwoPi)
                {
                    return;
                }

                rotation = value%MathHelper.TwoPi;
            }
        }

        public Vector3 Velocity { get; set; }

        public object Clone()
        {
            return new EntityState {Position = Position, Rotation = Rotation, Velocity = Velocity};
        }
    }
}