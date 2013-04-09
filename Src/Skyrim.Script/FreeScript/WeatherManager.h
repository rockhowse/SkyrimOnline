#pragma once

namespace FreeScript
{
	class WeatherManager
	{
	public:

		WeatherManager();

		void SetWeather(uint32_t pWeather);
		uint32_t GetWeather() const;
	};
}