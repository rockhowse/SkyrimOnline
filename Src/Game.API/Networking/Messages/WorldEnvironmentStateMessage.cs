#region

using Lidgren.Network;

#endregion

namespace Game.API.Networking.Messages
{
    public class WorldEnvironmentStateMessage
        : IGameMessage
    {
        public enum MessageSignature : byte
        {
            kPlayer,
            kServer,
            kSystem
        }

        public WorldEnvironmentStateMessage(NetIncomingMessage im)
        {
            Decode(im);
        }

        public WorldEnvironmentStateMessage()
        {
        }


        public float Hour { get; set; }

        public float Day { get; set; }

        public float Month { get; set; }

        public float Year { get; set; }

        public float TimeScale { get; set; }

        public int Weather { get; set; }

        public GameMessageTypes MessageType
        {
            get { return GameMessageTypes.WorldEnvironmentState; }
        }

        public void Decode(NetIncomingMessage im)
        {
            Hour = im.ReadFloat();
            Day = im.ReadFloat();
            Month = im.ReadFloat();
            Year = im.ReadFloat();
            TimeScale = im.ReadFloat();
            Weather = im.ReadInt32();
        }

        public void Encode(NetOutgoingMessage om)
        {
            om.Write(Hour);
            om.Write(Day);
            om.Write(Month);
            om.Write(Year);
            om.Write(TimeScale);
            om.Write(Weather);
        }
    }
}