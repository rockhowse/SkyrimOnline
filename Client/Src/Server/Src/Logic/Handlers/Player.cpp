
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
			{
				mController->GetCharacter()->SetHeading(transaction.GetHeading());
			}
			if(transaction.IsSetPosition())
			{
				BasicArray<3, float> position = transaction.GetPosition();
				mController->SetPosition(position[0], position[1], position[2]);
			}
			if(transaction.IsSetTime())
			{

			}
			if(transaction.IsSetSpeed())
			{

			}

		}
		//--------------------------------------------------------------------------------
		void Session::HandleMountState(Packet& data)
		{
		}
		//--------------------------------------------------------------------------------
	}
}