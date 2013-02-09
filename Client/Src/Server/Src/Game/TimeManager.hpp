#pragma once

namespace Skyrim
{
	namespace Game
	{
		class TimeManager
		{
		public:

			struct Date
			{
				float Hour, Day, Month, Year;
			};

			void Register(class ScriptEngine* engine);

			void SetTimeSpeed(float speed);
			void SetDate(Date& date);
			Date GetDate();
		};
	}
}