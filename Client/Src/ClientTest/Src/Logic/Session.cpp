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

			// Server side
			::Game::Player::Register(kClientChatMessage, &Session::HandleChatMessage);
			::Game::Player::Register(kClientInitialData, &Session::HandleInitialData);
			
		}
		//--------------------------------------------------------------------------------
		Session::Session(unsigned int id, ::Game::GameServer* server) : ::Game::Player(id, server) 
		{
			if(TheMassiveMessageMgr->Server() && Local())
			{
				/*TheMassiveMessageMgr->GetGOMDatabase()->Get<Game::PlayerGOMServer>()->
					Add(&TheGameWorld->GetPlayerCharacter(), ::Game::kTransactionFull, id);*/
			}
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

				_trace
			}
			catch(...)
			{
				System::Log::Debug("Session::~Session() error");
			}
		}
		//--------------------------------------------------------------------------------
		void Session::OnSynchronize()
		{
			_trace
			Framework::Network::Packet packet(kClientInitialData);


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

			packet << std::string("Kikoo")
				   << wornForms
				   << faceMorphs
				   << facePresets
				   << (uint32_t)13745
				   << (uint32_t)1;

			TheMassiveMessageMgr->SendMessageTo(::Game::kPlayerServer, packet);
			SendAwareness();
		}
		//--------------------------------------------------------------------------------
		std::string Session::GetName()
		{
			return mName;
		}
		//--------------------------------------------------------------------------------
	}
}