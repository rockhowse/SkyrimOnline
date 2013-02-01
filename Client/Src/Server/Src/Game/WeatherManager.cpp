#include "stdafx.h"
#include "WeatherManager.hpp"

namespace Skyrim
{
	namespace Game
	{
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
	}
}