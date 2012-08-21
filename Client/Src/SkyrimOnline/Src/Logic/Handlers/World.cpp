#include "stdafx.h"
#include <Logic/Session.h>
#include <Game/data.h>
#include <Overlay/Chat.h>
#include <Overlay/Interface.h>
#include <Overlay/ShardList.h>
#include <SkyrimOnline.h>

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
				float hour, day, month;
				data >> hour >> day >> month;
				SkyrimOnline::GetInstance().GetTimeManager().SetHour(hour);
				SkyrimOnline::GetInstance().GetTimeManager().SetDay(day);
				SkyrimOnline::GetInstance().GetTimeManager().SetMonth(month);
			}
			else if(service == "weatherman")
			{
				uint32_t weather;
				data >> weather;
				SkyrimOnline::GetInstance().GetWeatherManager().SetWeather(weather);
			}
		}
		//--------------------------------------------------------------------------------
	}
}