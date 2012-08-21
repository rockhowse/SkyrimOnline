#include "stdafx.h"
#include <Logic/Session.h>
#include <SkyrimOnline.h>

namespace Skyrim
{
	namespace Logic
	{
		//--------------------------------------------------------------------------------
		void Session::SendChatMessage(const std::string& pMessage)
		{	
			Network::Packet chat(Opcode::CMSG_CHAT_MESSAGE, 0xFFFFFFFF);
			chat << pMessage;
			Write(chat);
		}
		//--------------------------------------------------------------------------------
	}
}