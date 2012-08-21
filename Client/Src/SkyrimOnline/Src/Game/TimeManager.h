#pragma once

namespace Skyrim
{
	namespace Game
	{
		class TimeManager
		{
		public:

			TimeManager();

			void SetHour(float pHour);
			void SetDay(float pDay);
			void SetMonth(float pMonth);

			void Update(uint32_t pElapsed);

		private:

			static int DayPerMonth[12];

			float mHour;
			float mDay;
			float mMonth;
			float mTimeScale;
		};
	}
}