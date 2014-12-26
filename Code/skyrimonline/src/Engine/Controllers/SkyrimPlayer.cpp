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
				: m_pCharacter((Actor*)ScriptDragon::Game::GetPlayer())
				, m_pHorse(nullptr)
			{}

			SkyrimPlayer::~SkyrimPlayer()
			{}

			const std::string SkyrimPlayer::GetName()
			{
				TESNPC* pNpc = DYNAMIC_CAST(m_pCharacter->baseForm, TESForm, TESNPC);
				if (pNpc)
				{
					return pNpc->fullName.name.data;
				}
				return "ERROR";
			}

			void SkyrimPlayer::InitializeServerNode()
			{
				Messages::CliGame_PlayerInitializeSend* pPacket = new Messages::CliGame_PlayerInitializeSend;

				

				TheController->SendReliable(pPacket);
			}
		}
	}
}