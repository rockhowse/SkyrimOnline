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
			/*controller->InterpolateTo(px, py, pz, rx, ry, rz, 0);

			character->SetName(mName);

			character->SetFaceMorph(faceMorphs);
			character->SetFacePresets(facePresets);
			
			character->EquipItems(wornForms);
			//character->SetLevel(level);*/
		}
		//--------------------------------------------------------------------------------
	}
}