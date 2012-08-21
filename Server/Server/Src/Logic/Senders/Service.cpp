#include <Logic/Session.h>
#include <Logic/World.h>
#include <System/Tools.h>
#include <Opcodes.h>

namespace Skyrim
{
	namespace Logic
	{
		//---------------------------------------------------------------------
		void Session::SendServiceResponse(uint32_t pId, const std::string& pData1, const std::string& pData2, const std::string& pSignature)
		{
			/*Network::Packet packet(Opcode::SMSG_SIGNATURE_RESPONSE, 0xFFFFFFFF, 0x00);
			packet << (uint32_t)pId << pData1 << pData2 << pSignature;
			packet << (uint64_t)0 << "" << "" << (uint64_t)0;

			Write(packet);*/
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