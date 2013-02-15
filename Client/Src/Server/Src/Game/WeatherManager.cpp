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
		uint32_t WeatherManager::GetId()
		{
			return mWeather;
		}
		//--------------------------------------------------------------------------------
		void WeatherManager::SetWeather(uint32_t pWeather)
		{
			mWeather = pWeather;
		}
		//--------------------------------------------------------------------------------
		void WeatherManager::Register(ScriptEngine* engine)
		{
			engine->RegisterReferenceClass(WeatherManager);
			engine->RegisterMethod(WeatherManager, "void SetWeather(uint)", SetWeather);
			engine->RegisterMethod(WeatherManager, "uint GetWeatherForArea()", GetId);
		}
		//--------------------------------------------------------------------------------
	}
}