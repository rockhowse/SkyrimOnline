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
			ClientInitialTransaction transaction;

			transaction.SetName(TheGameWorld->GetUser());
			transaction.SetWornForms(TheGameWorld->GetPlayerCharacter().GetAllWornForms());
			transaction.SetFaceMorphs(TheGameWorld->GetPlayerCharacter().GetFaceMorph());
			transaction.SetFacePresets(TheGameWorld->GetPlayerCharacter().GetFacePresets());
			transaction.SetRace(TheGameWorld->GetPlayerCharacter().GetRace());
			transaction.SetGender(TheGameWorld->GetPlayerCharacter().GetGender());
			transaction.SetLevel(TheGameWorld->GetPlayerCharacter().GetLevel());
			transaction.GetPosition()[0] = TheGameWorld->GetPlayerCharacter().GetPosX();
			transaction.GetPosition()[1] = TheGameWorld->GetPlayerCharacter().GetPosY();
			transaction.GetPosition()[2] = TheGameWorld->GetPlayerCharacter().GetPosZ();
			transaction.GetRotation()[0] = TheGameWorld->GetPlayerCharacter().GetRotX();
			transaction.GetRotation()[1] = TheGameWorld->GetPlayerCharacter().GetRotY();
			transaction.GetRotation()[2] = TheGameWorld->GetPlayerCharacter().GetRotZ();

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