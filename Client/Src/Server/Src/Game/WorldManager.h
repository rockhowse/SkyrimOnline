#pragma once

#include "WeatherManager.hpp"
#include "TimeManager.hpp"
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
			ScriptEngine& GetScriptEngine();

			void SendWorldStateUpdate(WorldState& state);

			void Register();

		private:

			ScriptEngine mScript;
			WeatherManager mWeather;
			TimeManager mTime;
			
		};
	}
}