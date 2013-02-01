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
		}
		//--------------------------------------------------------------------------------
	}
}