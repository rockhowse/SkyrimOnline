#include "stdafx.h"
#include <Logic/Session.h>
#include <Game/data.h>
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
		}
		//--------------------------------------------------------------------------------
		void Session::HandleWorldState(Network::Packet& data)
		{
			WorldState transaction;
			data >> transaction;
			std::ostringstream os;
			os << "WorldState -> ";
			if(transaction.IsSetWeather())
			{
				os << " Weather : " << transaction.GetWeather();
			}
			if(transaction.IsSetDate())
			{
				os << " Hour : " << transaction.GetDate().get<0>()[0]
				<< " Day : " << transaction.GetDate().get<0>()[1]
				<< " Month : " << transaction.GetDate().get<0>()[2]
				<< " Year : " << transaction.GetDate().get<0>()[3];
			}
			System::Log::Debug(os.str());
		}
		//--------------------------------------------------------------------------------
	}
}