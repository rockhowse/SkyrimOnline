#include <Logic/Session.h>
#include <Logic/World.h>
#include <Network/Packet.h>
#include <System/Log.h>
#include <System/Tools.h>
#include <Opcodes.h>

using namespace Framework;

namespace Skyrim
{
	namespace Logic
	{
		//---------------------------------------------------------------------
		std::unordered_map<uint32_t, Session::CallBack> Session::mHandlers;
		//---------------------------------------------------------------------
		void Session::Setup()
		{
			mHandlers[Opcode::CMSG_REQUEST_CLOSE] = &Session::HandleRequestClose;
			mHandlers[Opcode::CMSG_SERVICE_ACK] = &Session::HandleServiceAck;
			mHandlers[Opcode::CMSG_SERVICE_REQUEST] = &Session::HandleServiceRequest;
			mHandlers[Opcode::CMSG_CHARACTER_INFO] = &Session::HandleCharacterInfo;
			mHandlers[Opcode::CMSG_MOVE_AND_LOOK] = &Session::HandlePositionAndLook;
			mHandlers[Opcode::CMSG_MOUNT_SPAWN] = &Session::HandleMount;
			mHandlers[Opcode::CMSG_MOUNT_REMOVE] = &Session::HandleUnmount;
			mHandlers[Opcode::CMSG_CHAT_MESSAGE] = &Session::HandleChatMessage;
			mHandlers[Opcode::CMSG_ENTER_REGION] = &Session::HandleEnterRegion;
		}
		//---------------------------------------------------------------------
		Session::Session(Framework::Network::TcpConnection::pointer pConnection, World* pWorld, uint32_t pId)
			: mConnection(pConnection), mWorld(pWorld), mId(pId), mRegion()
		{
			System::Log::Debug("New connection !");
		}
		//---------------------------------------------------------------------
		Session::~Session()
		{
			mConnection->Close();
			System::Log::Debug(std::string("User : ") + mAccount.Nicename + std::string(" left !"));
		}
		//---------------------------------------------------------------------
		void Session::Start()
		{
		}
		//---------------------------------------------------------------------
		void Session::Write(Framework::Network::Packet& pPacket)
		{
			mConnection->Write(Serialize(pPacket));
		}
		//---------------------------------------------------------------------
		void Session::Update(uint32_t pElapsed)
		{
			if(mConnection->IsOffline())
			{
				mWorld->GetMap()->LeaveRegion(mRegion, shared_from_this());
				mWorld->Remove(shared_from_this());
				return;
			}

			mChatJail.Update(pElapsed);

			while(mConnection->HasPacket())
			{
				Framework::Network::Packet data = PopPacket();
				try{
					switch(data.Type)
					{
					case Opcode::CMSG_PACKET:
						(this->*mHandlers.at(data.Opcode))(data);
						break;
					case Opcode::CMSG_PING:
						HandlePing(data);
						break;
					case Opcode::CMSG_HANDSHAKE:
						HandleHandshake(data);
						break;
					default:
						mConnection->Close();
						break;
					}
				}
				catch(std::exception& e)
				{
					System::Log::Debug(e.what());
					HandleBlackHole(data);
				}
			}
		}
		//---------------------------------------------------------------------
		std::string Session::GetName()
		{
			return mAccount.Nicename;
		}
		//---------------------------------------------------------------------
		unsigned int Session::GetId()
		{
			return mId;
		}
		//---------------------------------------------------------------------
		void Session::Broadcast(Framework::Network::Packet& pPacket)
		{
			
		}
		//---------------------------------------------------------------------
		Game::Character& Session::GetCharacter()
		{
			return mCharacter;
		}
		//---------------------------------------------------------------------
	}
}