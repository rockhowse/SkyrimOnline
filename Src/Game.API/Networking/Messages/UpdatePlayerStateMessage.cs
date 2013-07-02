using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Lidgren.Network;
using Microsoft.Xna.Framework;
using Game.API.Entities;

namespace Game.API.Networking.Messages
{
    public class UpdatePlayerStateMessage : IGameMessage
    {

        public UpdatePlayerStateMessage(NetIncomingMessage im)
        {
            this.Decode(im);
        }

        public UpdatePlayerStateMessage()
        {
        }

        public UpdatePlayerStateMessage(Player player)
        {
            this.Id = player.Id;
            this.Position = player.SimulationState.Position;
            this.Velocity = player.SimulationState.Velocity;
            this.Rotation = player.SimulationState.Rotation;
            this.MessageTime = NetTime.Now;
        }

        public long Id { get; set; }

        public double MessageTime { get; set; }

        public GameMessageTypes MessageType
        {
            get
            {
                return GameMessageTypes.UpdatePlayerState;
            }
        }

        public Vector3 Position { get; set; }

        public float Rotation { get; set; }

        public Vector3 Velocity { get; set; }

        public void Decode(NetIncomingMessage im)
        {
            this.Id = im.ReadInt64();
            this.MessageTime = im.ReadDouble();
            /*this.Position = im.ReadVector3();
            this.Velocity = im.ReadVector3();*/
            this.Rotation = im.ReadSingle();
        }

        public void Encode(NetOutgoingMessage om)
        {
            om.Write(this.Id);
            om.Write(this.MessageTime);
           /* om.Write(this.Position);
            om.Write(this.Velocity);*/
            om.Write(this.Rotation);
        }

    }
}
