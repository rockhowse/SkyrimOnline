
#include "stdafx.h"
#include <Logic/Session.h>
#include <Game/data.h>
#include <GameWorld.h>

namespace Skyrim
{
	namespace Logic
	{
		//--------------------------------------------------------------------------------
		void Session::HandleChatMessage(Packet& data)
		{
			//_trace
			try
			{
				ChatMessage message;
				data >> message;

				OnChatMessage(message.GetTheMessage());
				Framework::System::Log::Debug(string("Chat message received : ") + message.GetTheMessage());
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
	}
}