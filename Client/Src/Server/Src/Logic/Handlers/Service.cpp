#include <Logic/Session.h>
#include <Logic/World.h>
#include <System/Log.h>
#include <System/Tools.h>
#include <Opcodes.h>

using namespace Framework;

namespace Skyrim
{
	namespace Logic
	{
		//---------------------------------------------------------------------
		void Session::HandleChatMessage(Framework::Network::Packet& pData)
		{
			if(mChatJail.CanSend())
			{
				std::string str;
				pData >> str;
				if(str == "/online")
				{
					std::ostringstream os;
					os << "Total players online : " << mWorld->GetCount();
					SendChatMessage(os.str());
				}
				else
				{
					std::ostringstream os;
					if(mAccount.Level == 10)
					{
						os << "#00FFFF";
					}
					os << "[" << mAccount.Nicename << "]#FFFFFF says : " << str;

					Framework::Network::Packet packet(Opcode::SMSG_CHAT_MESSAGE, 0xFFFFFFFF);
					packet << os.str();
					mWorld->Broadcast(packet);
				}
			}
			else
			{
				SendChatMessage("SpamControl is unhappy ! Wait 5 seconds !");
			}
		}
		//---------------------------------------------------------------------
		void Session::HandleServiceRequest(Framework::Network::Packet& pPacket)
		{
			std::string serverType;
			std::string serviceName;
			std::string unk01, unk02;
			std::string serviceObjectName;
			std::string padding;
			std::string hash;

			pPacket >> serverType >> serviceName >> unk01 >> unk02 >> serviceObjectName >> padding >> hash;

			uint32_t responseid = 0;
			std::string sig = "";
			std::string data1 = "";

			if(serviceName == "timesource")
			{
				responseid = 0x010006;
				data1 = "timesource";
				sig = "462a9d1f";
			}
			else
			{
				std::ostringstream os;
				os << "Client requests : " << serviceName << "\nFrom : " << serverType << "\nRequires object : " << serviceObjectName << "\nHash : " << hash;
				System::Log::Debug(os.str());

				return;
			}

			SendServiceResponse(sig);
		}
		//---------------------------------------------------------------------
		void Session::HandleServiceAck(Framework::Network::Packet& pPacket)
		{
			uint16_t serviceId;
			std::string serviceObjectName;
			std::string hash;
			std::string origin;
			uint64_t timestamp;

			pPacket >> serviceId >> serviceObjectName >> hash >> origin >> timestamp;

			if(serviceObjectName == "OmegaServerProxyObjectName")
			{
				this->SendIntroduceConnection();
				this->SendClientInformation();
			}
			else
			{
				std::ostringstream os;
				os << "Client ack service[" << serviceId << "] : " << serviceObjectName << "\nFrom : " << origin << "\nHash : " << hash;
				System::Log::Debug(os.str());
			}
		}
		//---------------------------------------------------------------------
	}
}