#region

using System;

#endregion

namespace Game.API
{
    public class GameTimer
    {
        private long stopwatchStart;

        public GameTimer()
        {
            Reset();
        }

        public void Reset()
        {
            stopwatchStart = TimeGetTime();
        }

        public bool Stopwatch(int ms)
        {
            if (TimeGetTime() > stopwatchStart + ms)
            {
                Reset();
                return true;
            }

            return false;
        }

        private long TimeGetTime()
        {
            return DateTime.Now.Ticks/10000; // convert ticks to milliseconds. 10,000 ticks in 1 millisecond.
        }
    }
}