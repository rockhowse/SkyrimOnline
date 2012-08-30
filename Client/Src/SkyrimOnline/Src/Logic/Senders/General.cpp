#include "stdafx.h"
#include <Logic/NetEngine.hpp>
#include <SkyrimOnline.h>

namespace Skyrim
{
	namespace Logic
	{
		//--------------------------------------------------------------------------------
		void NetEngine::SendChatMessage(const std::string& pMessage)
		{	
			Network::Packet chat(Opcode::CMSG_CHAT_MESSAGE, 0xFFFFFFFF);
			chat << pMessage;

			Write(chat);
		}
		//--------------------------------------------------------------------------------
	}
}