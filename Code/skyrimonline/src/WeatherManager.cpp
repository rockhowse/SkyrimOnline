#include "WeatherManager.h"
#include <skyscript.h>
#include <cstdint>
#include "FreeScript.h"

namespace Skyrim
{

	//--------------------------------------------------------------------------------
	WeatherManager::WeatherManager()
	{
	}
	//--------------------------------------------------------------------------------
	void WeatherManager::SetWeather(uint32_t pWeather)
	{
		Weather::ForceActive((::TESWeather*)Game::GetFormById(pWeather), true);
	}
	//--------------------------------------------------------------------------------
	uint32_t WeatherManager::GetWeather() const
	{
		return ((TESForm*)Weather::GetCurrentWeather())->formID;
	}
	//--------------------------------------------------------------------------------

}