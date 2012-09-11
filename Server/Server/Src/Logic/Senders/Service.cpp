#include <Logic/Session.h>
#include <Logic/World.h>
#include <System/Tools.h>
#include <Opcodes.h>

namespace Skyrim
{
	namespace Logic
	{
		//---------------------------------------------------------------------
		void Session::SendServiceResponse(const std::string& pSignature)
		{
			Framework::Network::Packet packet(Opcode::SMSG_SIGNATURE_RESPONSE, 0xFFFFFFFF, 0x00);
			packet << pSignature;

			Write(packet);
		}
		//---------------------------------------------------------------------
		void Session::SendServiceTimesource(float pHour, float pDay, float pMonth)
		{
			Framework::Network::Packet packet(Opcode::SMSG_SIGNATURE_RESPONSE, 0xFFFFFFFF, 0x00);
			packet << std::string("timesource");
			packet << pHour << pDay << pMonth;

			Write(packet);
		}
		//---------------------------------------------------------------------
	}
}