#include "stdafx.h"
#include "WeatherManager.hpp"
#include "GameWorld.h"
#include "ScriptEngine.hpp"

namespace Skyrim
{
	namespace Game
	{
		//--------------------------------------------------------------------------------
		WeatherManager::WeatherManager()
		{
		}
		//--------------------------------------------------------------------------------
		void WeatherManager::Update(float pDelta)
		{

		}
		//--------------------------------------------------------------------------------
		uint32_t WeatherManager::GetWeatherForArea(uint32_t pArea)
		{
			return ID_TESWeather::FXWthrSunlight;
			//return mWeathers[pArea];
		}
		//--------------------------------------------------------------------------------
		void WeatherManager::SetWeather(uint32_t pWeather)
		{
			Framework::System::Log::Debug("Set weather !");
		}
		//--------------------------------------------------------------------------------
		void WeatherManager::Register(ScriptEngine* engine)
		{
			engine->RegisterReferenceClass("WeatherManager");
			engine->RegisterGlobal("WeatherManager Weather", this);
			engine->RegisterMethod("WeatherManager", "void SetWeather(uint)", asMETHOD(WeatherManager, SetWeather));
		}
		//--------------------------------------------------------------------------------
	}
}