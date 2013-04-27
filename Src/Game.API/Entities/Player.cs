using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Microsoft.Xna.Framework;

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
            get
            {
                return this.isInvulnerable;
            }

            set
            {
                if (this.isInvulnerable == value)
                {
                    return;
                }

                this.isInvulnerable = value;
                if (this.isInvulnerable)
                {

                }
            }
        }

        public override void Update(GameTime gameTime)
        {
            if (this.IsDestroyed)
            {

            }

            if (this.IsInvulnerable)
            {
                this.IsInvulnerable = false;
            }

            if (!this.IsDestroyed)
            {
                base.Update(gameTime);
            }
        }

    }
}
