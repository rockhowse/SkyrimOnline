#pragma once

#include "WeatherManager.hpp"

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
		};
	}
}