#pragma once

#include "skyscript.h"
#include <cstdint>

namespace Skyrim
{
	class WeatherManager
	{
	public:

		WeatherManager();

		void SetWeather(uint32_t pWeather);
		uint32_t GetWeather() const;
	};
}