using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Microsoft.Xna.Framework;

namespace Game.API.Entities
{
    public class SkyrimObject
    {
        internal SkyrimObject(
            long id,
            EntityState simulationState)
        {
            this.Id = id;

            this.SimulationState = simulationState;
            this.DisplayState = (EntityState)simulationState.Clone();
            this.PrevDisplayState = (EntityState)simulationState.Clone();
        }

        public EntityState DisplayState { get; set; }

        public bool EnableSmoothing { get; set; }

        public long Id { get; set; }

        public double LastUpdateTime { get; set; }

        public EntityState PrevDisplayState { get; set; }

        public EntityState SimulationState { get; set; }

        public virtual void Update(GameTime gameTime)
        {
            var elapsedSeconds = (float)gameTime.ElapsedGameTime.TotalSeconds;
            this.SimulationState.Position += this.SimulationState.Velocity * elapsedSeconds;

            if (this.EnableSmoothing)
            {
                this.PrevDisplayState.Position += this.PrevDisplayState.Velocity * elapsedSeconds;
                this.ApplySmoothing(1 / 12f);
            }
            else
            {
                this.DisplayState = (EntityState)this.SimulationState.Clone();
            }
        }

        private void ApplySmoothing(float delta)
        {
            this.DisplayState.Position = Vector3.Lerp(this.PrevDisplayState.Position, this.SimulationState.Position, delta);
            this.DisplayState.Velocity = Vector3.Lerp(this.PrevDisplayState.Velocity, this.SimulationState.Velocity, delta);
            this.DisplayState.Rotation = MathHelper.Lerp(this.PrevDisplayState.Rotation, this.SimulationState.Rotation, delta);
            this.PrevDisplayState = (EntityState)this.DisplayState.Clone();
        }
    }
}
