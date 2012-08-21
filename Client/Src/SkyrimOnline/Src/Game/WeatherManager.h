#pragma once

namespace Skyrim
{
	namespace Game
	{
		class WeatherManager
		{
		public:

			WeatherManager();

			void SetWeather(uint32_t pWeather);

			void Update(uint32_t pElapsed);

		private:

			uint32_t mWeather;
		};
	}
}