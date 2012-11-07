#include "stdafx.h"
#include <Logic/Session.h>
#include <Game/data.h>
#include <Overlay/Chat.h>
#include <Overlay/System.h>
#include <Overlay/Message.h>
#include <Overlay/ShardList.h>
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
				TimeManager::Date date;
				data >> date.Hour >> date.Day >> date.Month;
				TheGameWorld->GetTimeManager().SetDate(date);
			}
			else if(service == "weatherman")
			{
				uint32_t weather;
				data >> weather;
				TheGameWorld->GetWeatherManager().SetWeather(weather);
			}
			else if(service == "cipher")
			{
				Overlay::TheMessage->Hide();
				TheGameWorld->SetState("InGame");
			}
		}
		//--------------------------------------------------------------------------------
	}
}