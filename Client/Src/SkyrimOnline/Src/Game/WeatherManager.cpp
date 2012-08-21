#include "stdafx.h"
#include "WeatherManager.h"

namespace Skyrim
{
	namespace Game
	{
		//--------------------------------------------------------------------------------
		WeatherManager::WeatherManager()
			:mWeather(0)
		{
		}
		//--------------------------------------------------------------------------------
		void WeatherManager::SetWeather(uint32_t pWeather)
		{
			mWeather = pWeather;
		}
		//--------------------------------------------------------------------------------
		void WeatherManager::Update(uint32_t pElapsed)
		{
			if(Form::GetFormID((TESForm*)Weather::GetCurrentWeather()) != mWeather && mWeather != 0)
			{
				Weather::ForceActive((TESWeather*)::Game::GetFormById(mWeather), true);
			}
		}
		//--------------------------------------------------------------------------------
	}
}