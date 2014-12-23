#pragma once

#include <stdafx.h>

#include <Engine/Controllers/SkyrimController.h>
#include <skyscript.h>
#include <GameForms.h>
#include <GameReferences.h>
#include <GameObjects.h>
#include <GameRTTI.h>

namespace Logic
{
	namespace Engine
	{
		namespace Controllers
		{
			SkyrimPlayer::SkyrimPlayer()
				: m_pPlayer((Actor*)ScriptDragon::Game::GetPlayer())
			{}

			SkyrimPlayer::~SkyrimPlayer()
			{}

			const std::string SkyrimPlayer::GetName()
			{
				TESNPC* pNpc = DYNAMIC_CAST(m_pPlayer->baseForm, TESForm, TESNPC);
				if (pNpc)
				{
					return pNpc->fullName.name.data;
				}
				return "ERROR";
			}
		}
	}
}