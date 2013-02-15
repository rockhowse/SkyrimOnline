#include "stdafx.h"
#include "Area.hpp"
#include "ScriptEngine.hpp"

namespace Skyrim
{
	namespace Game
	{
		//--------------------------------------------------------------------------------
		void Area::Register(class ScriptEngine* engine)
		{
			engine->RegisterReferenceClass(Area);
			engine->RegisterMethod(Area, "WeatherManager@ GetWeather()", GetWeather);
		}
		//--------------------------------------------------------------------------------
		WeatherManager* Area::GetWeather()
		{
			return &mWeather;
		}
		//--------------------------------------------------------------------------------
	}
}