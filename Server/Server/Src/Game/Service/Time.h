#pragma once

#include <boost/timer.hpp>
#include <cstdint>

namespace Swtor{
namespace Game{
	namespace Service
	{
		class Time
		{
		public:

			Time();

			uint32_t GetTick();

			void Update(float pElapsed);

		private:

			float mTimeScale;
		};
	}
}
}