#include "stdafx.h"
#include <Logic/Session.h>
#include <Game/ActorController.h>
#include <Game/PlayerGOMServer.h>
#include <GameWorld.h>

namespace Skyrim
{
	namespace Logic
	{
		//--------------------------------------------------------------------------------
		void Session::HandleInitialData(Network::Packet& pPacket)
		{
			ClientInitialTransaction transaction;
			pPacket >> transaction;

			mController = boost::make_shared<Game::ActorController>(transaction.GetRace(), transaction.GetGender());

			TheMassiveMessageMgr->GetGOMDatabase()->Get<Game::PlayerGOMServer>()->_Add(mController, ::Game::kTransactionFull, GetKey());

			auto character = mController->GetCharacter();
			character->SetName(transaction.GetName());

			mController->SetPosition(transaction.GetPosition()[0], transaction.GetPosition()[1], transaction.GetPosition()[2]);
			mController->SetRotation(transaction.GetRotation()[0], transaction.GetRotation()[1], transaction.GetRotation()[2]);

			character->SetFaceMorph(transaction.GetFaceMorphs());
			character->SetFacePresets(transaction.GetFacePresets());
			
			character->EquipItems(transaction.GetWornForms());
		}
		//--------------------------------------------------------------------------------
	}
}