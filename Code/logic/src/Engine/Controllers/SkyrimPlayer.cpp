#pragma once

#include <stdafx.h>

#include <Engine/Controllers/SkyrimController.h>
#include <skyrim/SkyrimEngine.h>
#include <skyrim/Actor.h>
#include <skyrim/ReferencesHelper.h>
#include <skyrim/FormsHelper.h>

namespace Logic
{
	namespace Engine
	{
		namespace Controllers
		{
			SkyrimPlayer::SkyrimPlayer()
				: m_pPlayer(Skyrim::GetPlayer())
			{}

			SkyrimPlayer::~SkyrimPlayer()
			{}

			const std::string SkyrimPlayer::GetName()
			{
				Skyrim::ActorHelper actorHelper(m_pPlayer);
				Skyrim::TESNPCHelper npcHelper(actorHelper.GetNpc());

				return npcHelper.GetName();
			}
		}
	}
}