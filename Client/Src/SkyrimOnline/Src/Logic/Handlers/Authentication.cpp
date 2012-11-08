#include "stdafx.h"
#include <Logic/Session.h>
#include <Game/data.h>
#include <Game/ActorController.h>
#include <Game/PlayerGOMServer.h>
#include <Overlay/Chat.h>
#include <Overlay/System.h>
#include <Overlay/ShardList.h>
#include <GameWorld.h>

namespace Skyrim
{
	namespace Logic
	{
		//--------------------------------------------------------------------------------
		void Session::HandleInitialData(Network::Packet& pPacket)
		{
			std::vector<float> faceMorphs;
			std::vector<uint32_t> wornForms;
			float px, py, pz, rx, ry, rz;
			uint32_t race, gender, level;
			pPacket >> mName
				>> wornForms
				>> faceMorphs
				>> race
				>> gender
				>> level
				>> px >> py >> pz >> rx >> ry >> rz;

			/*Game::ActorController* controller = new Game::ActorController(race, gender);
			TheMassiveMessageMgr->GetGOMDatabase()->Get<Game::PlayerGOMServer>()->Add(controller->GetCharacter().get(), ::Game::kTransactionFull, GetKey());
			auto character = controller->GetCharacter();

			controller->InterpolateTo(px, py, pz, rx, ry, rz, 0);

			character->SetFaceMorph(faceMorphs);
			character->SetName(mName);
			character->EquipItems(wornForms);
			character->SetLevel(level);*/

			_trace
		}
		//--------------------------------------------------------------------------------
	}
}