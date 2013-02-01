
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
				ChatMessage message;
				data >> message;
				TheMassiveMessageMgr->SendMessageAll(message.ToPacket(kServerChatMessage));
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
		void Session::HandlePlayerMoveState(Packet& data)
		{
			PlayerMoveState transaction;
			data >> transaction;

			if(transaction.IsSetHeading())
				mController->GetCharacter()->SetHeading(transaction.GetHeading());
		}
		//--------------------------------------------------------------------------------
		void Session::HandleMountState(Packet& data)
		{
		}
		//--------------------------------------------------------------------------------
	}
}