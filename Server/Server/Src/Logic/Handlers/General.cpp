#include <Logic/Session.h>
#include <Logic/World.h>
#include <System/Log.h>
#include <System/Tools.h>
#include <Opcodes.h>

namespace Skyrim
{
	namespace Logic
	{
		//---------------------------------------------------------------------
		void Session::HandlePing(Framework::Network::Packet& pPacket)
		{
			Framework::Network::Packet packet(pPacket.Opcode, 0, Opcode::SMSG_PING);
			packet << "";

			Write(packet);
		}
		//---------------------------------------------------------------------
		void Session::HandleBlackHole(Framework::Network::Packet& pPacket)
		{
			std::ostringstream os;
			os << "Unknown opcode : 0x" << std::hex << pPacket.Opcode;
			Framework::System::PrintBinary((uint8_t*)pPacket.GetBuffer().data(), pPacket.GetBuffer().size(), os.str());
		}
		//---------------------------------------------------------------------
	}
}