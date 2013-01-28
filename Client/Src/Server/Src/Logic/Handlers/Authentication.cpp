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
			/*std::vector<float> faceMorphs;
			std::vector<uint32_t> wornForms;
			std::vector<uint32_t> facePresets;
			float px, py, pz, rx = 0, ry = 0, rz = 0;
			uint32_t race, gender, level;
			pPacket >> mName
				>> wornForms
				>> faceMorphs
				>> facePresets
				>> race
				>> gender
				>> level
				>> px >> py >> pz >> rx >> ry >> rz;

			auto controller = boost::make_shared<Game::ActorController>(race, gender);
			TheMassiveMessageMgr->GetGOMDatabase()->Get<Game::PlayerGOMServer>()->_Add(controller, ::Game::kTransactionFull, GetKey());
			auto character = controller->GetCharacter();

			controller->InterpolateTo(px, py, pz, rx, ry, rz, 0);

			character->SetName(mName);

			character->SetFaceMorph(faceMorphs);
			character->SetFacePresets(facePresets);
			
			character->EquipItems(wornForms);
			//character->SetLevel(level);*/

			_trace
		}
		//--------------------------------------------------------------------------------
	}
}