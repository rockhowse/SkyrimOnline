#pragma once

#include "WeatherManager.hpp"
#include "ScriptEngine.hpp"

namespace Skyrim
{
	namespace Game
	{
		class WorldManager
		{
		public:

			WorldManager();
			~WorldManager();

			void Update(float pDelta);


			WorldState GetWorldState();

		private:

			WeatherManager mWeather;
			ScriptEngine mScript;
		};
	}
}