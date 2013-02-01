#pragma once

namespace Skyrim
{
	namespace Game
	{
		class WeatherManager
		{
		public:

			void Update(float pDelta);
			
			uint32_t GetWeatherForArea(uint32_t pArea);

			boost::signal<void(uint32_t, uint32_t)> OnWeather;

		private:

			typedef std::map<uint32_t, uint32_t> AreaWeather;

			AreaWeather mWeathers;

		};
	}
}