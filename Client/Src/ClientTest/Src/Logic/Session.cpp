#include "stdafx.h"
#include "Session.h"
#include <Game/data.h>
#include <Game/PlayerGOMServer.h>
#include <GameWorld.h>
#include <Network/IoServicePool.h>

namespace Skyrim
{
	namespace Logic
	{
		//--------------------------------------------------------------------------------
		void Session::Init()
		{
			::Game::Player::Register(kServerChatMessage, &Session::HandleChatMessage);
			::Game::Player::Register(kServerWorldState,  &Session::HandleWorldState);
			
		}
		//--------------------------------------------------------------------------------
		Session::Session(unsigned int id, ::Game::GameServer* server) : ::Game::Player(id, server) 
		{
		}
		//--------------------------------------------------------------------------------
		Session::~Session()
		{
			try
			{
				std::for_each(mEventLinks.begin(), mEventLinks.end(), [](boost::signals::connection& pConnection)
				{
					pConnection.disconnect();
				});
			}
			catch(...)
			{
				System::Log::Debug("Session::~Session() error");
			}
		}
		//--------------------------------------------------------------------------------
		void Session::OnSynchronize()
		{
			ClientInitialTransaction transaction;

			std::vector<uint32_t> wornForms;
			wornForms.push_back(0x13edb);
			wornForms.push_back(0xa6d7b);
			wornForms.push_back(0xa6d7d);
			wornForms.push_back(0x13ed7);
			wornForms.push_back(0x13914);
			wornForms.push_back(0x13edb);

			std::vector<uint32_t> facePresets;
			facePresets.push_back(0);

			std::vector<float> faceMorphs;
			faceMorphs.push_back(0);
			faceMorphs.push_back(0);
			faceMorphs.push_back(1);
			faceMorphs.push_back(0);
			faceMorphs.push_back(0);
			faceMorphs.push_back(0);
			faceMorphs.push_back(0);
			faceMorphs.push_back(0);
			faceMorphs.push_back(0);
			faceMorphs.push_back(0);
			faceMorphs.push_back(0);
			faceMorphs.push_back(0);
			faceMorphs.push_back(0.18f);
			faceMorphs.push_back(1);
			faceMorphs.push_back(0);
			faceMorphs.push_back(0);
			faceMorphs.push_back(0);
			faceMorphs.push_back(0);
			faceMorphs.push_back(0);

			transaction.SetName(std::string(std::to_string((long long)time(0))));
			transaction.SetFaceMorphs(faceMorphs);
			transaction.SetWornForms(wornForms);
			transaction.SetGender(1);
			transaction.SetFacePresets(facePresets);
			transaction.SetLevel(10);
			transaction.SetRace(13745);

			// Reverse send order will cause duplications
			SendAwareness();

			TheMassiveMessageMgr->SendMessageTo(::Game::kPlayerServer, transaction.ToPacket(kClientInitialData));
			
		}
		//--------------------------------------------------------------------------------
		std::string Session::GetName()
		{
			return mName;
		}
		//--------------------------------------------------------------------------------
	}
}