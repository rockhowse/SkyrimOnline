#region

using Microsoft.Xna.Framework;

#endregion

namespace Game.API.Entities
{
    public class GameObject
    {
        internal GameObject(
            long id,
            EntityState simulationState)
        {
            Id = id;

            SimulationState = simulationState;
            DisplayState = (EntityState) simulationState.Clone();
            PrevDisplayState = (EntityState) simulationState.Clone();
        }

        public EntityState DisplayState { get; set; }

        public bool EnableSmoothing { get; set; }

        public long Id { get; set; }

        public double LastUpdateTime { get; set; }

        public EntityState PrevDisplayState { get; set; }

        public EntityState SimulationState { get; set; }

        public virtual void Update(GameTime gameTime)
        {
            var elapsedSeconds = (float) gameTime.ElapsedGameTime.TotalSeconds;
            SimulationState.Position += SimulationState.Velocity*elapsedSeconds;

            if (EnableSmoothing)
            {
                PrevDisplayState.Position += PrevDisplayState.Velocity*elapsedSeconds;
                ApplySmoothing(1/12f);
            }
            else
            {
                DisplayState = (EntityState) SimulationState.Clone();
            }
        }

        private void ApplySmoothing(float delta)
        {
            DisplayState.Position = Vector3.Lerp(PrevDisplayState.Position, SimulationState.Position, delta);
            DisplayState.Velocity = Vector3.Lerp(PrevDisplayState.Velocity, SimulationState.Velocity, delta);
            DisplayState.Rotation = MathHelper.Lerp(PrevDisplayState.Rotation, SimulationState.Rotation, delta);
            PrevDisplayState = (EntityState) DisplayState.Clone();
        }
    }
}