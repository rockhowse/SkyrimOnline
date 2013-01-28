#include "stdafx.h"
#include <Logic/Session.h>
#include <GameWorld.h>

namespace Skyrim
{
	namespace Logic
	{
		//--------------------------------------------------------------------------------
		void Session::HandleServiceResponse(Network::Packet& data)
		{
			std::string service;
			data >> service;

			System::Log::Debug(std::string("Register service : ") + service);
			if(service == "timesource")
			{
//				Game::TimeManager::Date date;
//				data >> date.Hour >> date.Day >> date.Month;
			//	TheGameWorld->GetTimeManager().SetDate(date);
			}
			else if(service == "weatherman")
			{
				uint32_t weather;
				data >> weather;
			//	TheGameWorld->GetWeatherManager().SetWeather(weather);
			}
		}
		//--------------------------------------------------------------------------------
	}
}