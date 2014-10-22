#pragma once

namespace Skyrim
{
	class TimeManager
	{
	public:

		struct Date
		{
			float Hour, Day, Month, Year;
		};

		TimeManager();

		void SetDate(const Date& pDate);
		Date GetDate();

	private:

		static int DayPerMonth[12];
	};
}