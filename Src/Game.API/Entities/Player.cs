#region

using Microsoft.Xna.Framework;

#endregion

namespace Game.API.Entities
{
    public class Player : GameObject
    {
        private bool isInvulnerable;

        internal Player(long id, EntityState simulationState) : base(id, simulationState)
        {
        }

        public bool IsDestroyed { get; set; }

        public bool IsInvulnerable
        {
            get { return isInvulnerable; }

            set
            {
                if (isInvulnerable == value)
                {
                    return;
                }

                isInvulnerable = value;
                if (isInvulnerable)
                {
                }
            }
        }

        public override void Update(GameTime gameTime)
        {
            if (IsDestroyed)
            {
            }

            if (IsInvulnerable)
            {
                IsInvulnerable = false;
            }

            if (!IsDestroyed)
            {
                base.Update(gameTime);
            }
        }
    }
}