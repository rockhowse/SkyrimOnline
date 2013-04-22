using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Skyrim.API
{
    public class GameTimer
    {
        private long stopwatchStart;

        public GameTimer()
        {
            this.Reset();
        }

        public void Reset()
        {
            this.stopwatchStart = this.TimeGetTime();
        }

        public bool Stopwatch(int ms)
        {
            if (this.TimeGetTime() > this.stopwatchStart + ms)
            {
                this.Reset();
                return true;
            }

            return false;
        }

        private long TimeGetTime()
        {
            return DateTime.Now.Ticks / 10000; // convert ticks to milliseconds. 10,000 ticks in 1 millisecond.
        }

    }
}
