#include "stdafx.h"
#include "Session.h"
#include <Game/PlayerGOMServer.h>
#include <GameWorld.h>

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
				TheMassiveMessageMgr->GetGOMDatabase()->Get<Game::PlayerGOMServer>()->
					Add(&TheGameWorld->GetPlayerCharacter(), ::Game::kTransactionFull, id);
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

				TheMassiveMessageMgr->GetGOMDatabase()->Get<Game::PlayerGOMServer>()->Remove(::Game::kTransactionFull, GetKey());

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

			packet << TheGameWorld->GetUser()
				   << TheGameWorld->GetPlayerCharacter().GetAllWornForms()
				   << TheGameWorld->GetPlayerCharacter().GetFaceMorph()
				   << TheGameWorld->GetPlayerCharacter().GetFacePresets()
				   << TheGameWorld->GetPlayerCharacter().GetRace()
				   << TheGameWorld->GetPlayerCharacter().GetGender()
				   << TheGameWorld->GetPlayerCharacter().GetLevel()
				   << TheGameWorld->GetPlayerCharacter().GetPosX()
				   << TheGameWorld->GetPlayerCharacter().GetPosY()
				   << TheGameWorld->GetPlayerCharacter().GetPosZ()
				   << TheGameWorld->GetPlayerCharacter().GetRotX()
				   << TheGameWorld->GetPlayerCharacter().GetRotY()
				   << TheGameWorld->GetPlayerCharacter().GetRotZ();

			TheMassiveMessageMgr->SendMessageTo(::Game::kPlayerServer, packet);
		}
		//--------------------------------------------------------------------------------
		std::string Session::GetName()
		{
			return mName;
		}
		//--------------------------------------------------------------------------------
	}
}