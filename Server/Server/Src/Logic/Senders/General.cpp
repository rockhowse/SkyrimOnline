#include <Logic/Session.h>
#include <Logic/World.h>
#include <System/Tools.h>
#include <Opcodes.h>

namespace Skyrim
{
	namespace Logic
	{
		//---------------------------------------------------------------------
		void Session::SendChatMessage(const std::string& pMessage)
		{
			Framework::Network::Packet packet(Opcode::SMSG_CHAT_MESSAGE, 0xFFFFFFFF);

			packet << pMessage;

			Write(packet);
		}
		//---------------------------------------------------------------------
	}
}