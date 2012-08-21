#include "stdafx.h"
#include "Session.h"
#include <Game/data.h>
#include <Overlay/Chat.h>
#include <Overlay/Interface.h>
#include <SkyrimOnline.h>
#include <Network/IoServicePool.h>

namespace Skyrim
{
	namespace Logic
	{
		//--------------------------------------------------------------------------------
		static Network::IoServicePool gIoPool(1);
		std::unordered_map<unsigned int, Session::CallBack> Session::mHandlers;
		//--------------------------------------------------------------------------------
		void Session::Init()
		{
			gIoPool.Run();

			mHandlers[Opcode::SMSG_PLAYER_SPAWN] = &Session::HandlePlayerSpawn;
			mHandlers[Opcode::SMSG_PLAYER_MOVE_AND_LOOK] = &Session::HandlePlayerMoveAndLook;
			mHandlers[Opcode::SMSG_CHARACTER_REMOVE] = &Session::HandlePlayerRemove;
			mHandlers[Opcode::SMSG_CHAT_MESSAGE] = &Session::HandleChatMessage;
			mHandlers[Opcode::SMSG_SIGNATURE_RESPONSE] = &Session::HandleServiceResponse;
			mHandlers[Opcode::SMSG_PLAYER_MOUNT_SPAWN] = &Session::HandleMount;
			mHandlers[Opcode::SMSG_PLAYER_MOUNT_REMOVE] = &Session::HandleUnmount;
		}
		//--------------------------------------------------------------------------------
		Session::Session(Game::PlayerWatcher& pPlayer)
		{
			mEventLinks.push_back(pPlayer.OnEnterWorld.connect(boost::bind(&Session::SendCharacterInfo, this, _1)));
			mEventLinks.push_back(pPlayer.OnMove      .connect(boost::bind(&Session::SendMoveAndLook,   this, _1, _2)));
			mEventLinks.push_back(pPlayer.OnMount     .connect(boost::bind(&Session::SendMount,         this, _1)));
			mEventLinks.push_back(pPlayer.OnUnmount   .connect(boost::bind(&Session::SendUnmount,       this)));
			mEventLinks.push_back(pPlayer.OnRegion    .connect(boost::bind(&Session::SendEnterRegion,     this, _1)));
		}
		//--------------------------------------------------------------------------------
		Session::~Session()
		{
			try{
				std::for_each(mEventLinks.begin(), mEventLinks.end(), [](boost::signals::connection& pConnection)
				{
					pConnection.disconnect();
				});

				System::Log::Debug("Session::~Session()");
			}
			catch(...)
			{
				System::Log::Debug("Session::~Session() error");
			}
			System::Log::Debug("alright !");
		}
		//--------------------------------------------------------------------------------
		void Session::Write(Network::Packet& msg)
		{
			mConnection->Write(Serialize(msg));
		}
		//--------------------------------------------------------------------------------
		bool Session::IsOffline()
		{
			if(mConnection)
				return mConnection->IsOffline();
			return true;
		}
		//--------------------------------------------------------------------------------
		void Session::Update(float pDelta)
		{
			if(mConnection)
				while(HasPacket())
				{
					Network::Packet data = PopPacket();
					try{
						(this->*mHandlers.at(data.Opcode))(data);
					}
					catch(const std::out_of_range&)
					{
					}
				}
		}
		//--------------------------------------------------------------------------------
		void Session::SetCipher(Crypt::Cipher* pCipher)
		{
			mCipher.reset(pCipher);
			mConnection->Start();
		}
		//--------------------------------------------------------------------------------
		void Session::Connect(const std::string& pAddress, const std::string& pPort)
		{
			mConnection.reset(new Network::TcpConnection(gIoPool.GetIoService()));
			mConnection->OnConnect.connect(boost::bind(&SkyrimOnline::OnConnect, &SkyrimOnline::GetInstance(), _1));
			mConnection->SetStrategy(this);
			mConnection->Connect(pAddress, pPort);
		}
		//--------------------------------------------------------------------------------
	}
}