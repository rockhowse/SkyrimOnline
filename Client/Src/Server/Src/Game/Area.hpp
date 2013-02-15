#pragma once

#include "WeatherManager.hpp"

namespace Skyrim
{
	namespace Game
	{
		class Area
		{
		public:

			static void Register(class ScriptEngine* engine);

			WeatherManager* GetWeather();

		private:

			WeatherManager mWeather;
		};
	}
}