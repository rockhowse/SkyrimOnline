#region

using Game.API.Entities;
using Lidgren.Network;
using Microsoft.Xna.Framework;

#endregion

namespace Game.API.Networking.Messages
{
    public class UpdatePlayerStateMessage : IGameMessage
    {
        public UpdatePlayerStateMessage(NetIncomingMessage im)
        {
            Decode(im);
        }

        public UpdatePlayerStateMessage()
        {
        }

        public UpdatePlayerStateMessage(Player player)
        {
            Id = player.Id;
            Position = player.SimulationState.Position;
            Velocity = player.SimulationState.Velocity;
            Rotation = player.SimulationState.Rotation;
            MessageTime = NetTime.Now;
        }

        public long Id { get; set; }

        public double MessageTime { get; set; }

        public Vector3 Position { get; set; }

        public float Rotation { get; set; }

        public Vector3 Velocity { get; set; }

        public GameMessageTypes MessageType
        {
            get { return GameMessageTypes.UpdatePlayerState; }
        }

        public void Decode(NetIncomingMessage im)
        {
            Id = im.ReadInt64();
            MessageTime = im.ReadDouble();
            /*this.Position = im.ReadVector3();
            this.Velocity = im.ReadVector3();*/
            Rotation = im.ReadSingle();
        }

        public void Encode(NetOutgoingMessage om)
        {
            om.Write(Id);
            om.Write(MessageTime);
            /* om.Write(this.Position);
            om.Write(this.Velocity);*/
            om.Write(Rotation);
        }
    }
}