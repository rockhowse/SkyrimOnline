#include "stdafx.h"
#include "WeatherManager.h"

namespace FreeScript
{

	//--------------------------------------------------------------------------------
	WeatherManager::WeatherManager()
	{
	}
	//--------------------------------------------------------------------------------
	void WeatherManager::SetWeather(uint32_t pWeather)
	{
		Weather::ForceActive((TESWeather*)::Game::GetFormById(pWeather), true);
	}
	//--------------------------------------------------------------------------------
	uint32_t WeatherManager::GetWeather() const
	{
		return Form::GetFormID((TESForm*)Weather::GetCurrentWeather());
	}
	//--------------------------------------------------------------------------------

}