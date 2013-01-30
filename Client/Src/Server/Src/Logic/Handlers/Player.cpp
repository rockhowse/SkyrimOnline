
#include "stdafx.h"
#include <Logic/Session.h>
#include <GameWorld.h>

namespace Skyrim
{
	namespace Logic
	{
		//--------------------------------------------------------------------------------
		void Session::HandleChatMessage(Packet& data)
		{
			_trace
			try
			{
				if(data.Opcode == kClientChatMessage)
				{
					data.Opcode = kServerChatMessage;
					TheMassiveMessageMgr->SendMessageAll(data);
					return;
				}
				std::string msg;
				data >> msg;
			}
			catch(boost::exception& e)
			{
				System::Log::Error(boost::diagnostic_information(e));
			}
			catch(std::exception& e)
			{
				System::Log::Error(e.what());
			}
		}
		//--------------------------------------------------------------------------------
		void Session::HandlePlayerSpawn(Packet& data)
		{
			try
			{
			}
			catch(boost::exception& e)
			{
				System::Log::Error(boost::diagnostic_information(e));
			}
			catch(std::exception& e)
			{
				System::Log::Error(e.what());
			}
		}
		//--------------------------------------------------------------------------------
		void Session::HandlePlayerMoveAndLook(Packet& data)
		{
		}
		//--------------------------------------------------------------------------------
		void Session::HandlePlayerRemove(Packet& data)
		{
		}
		//--------------------------------------------------------------------------------
		void Session::HandleMount(Packet& data)
		{
		}
		//--------------------------------------------------------------------------------
		void Session::HandleUnmount(Packet& data)
		{
		}
		//--------------------------------------------------------------------------------
	}
}