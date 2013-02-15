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

			WorldState GetWorldState(const std::string& pArea);
			ScriptEngine& GetScriptEngine();

			void SendWorldStateUpdate(WorldState& state);

			void Register();

			class Area* GetArea(const std::string& pArea);

		private:

			typedef std::map<std::string, Area> AreaMap;

			AreaMap mAreas;

			ScriptEngine mScript;
			TimeManager mTime;
			
		};
	}
}