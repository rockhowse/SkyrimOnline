#pragma once

#include <stdafx.h>

#include <Engine/Controllers/SkyrimTest.h>
#include <skyscript.h>
#include <enums.h>
#include <GameRTTI.h>
#include <mhook.h>
#include <PapyrusVM.h>
#include <GameForms.h>
#include <GameObjects.h>

namespace Logic
{
	namespace Engine
	{
		namespace Controllers
		{
			std::fstream f("test.log", std::ios::trunc | std::ios::out);
			SkyrimTest::SkyrimTest()
				: m_jumped(false)
			{
				ScriptDragon::TESObjectREFR* pMe = (ScriptDragon::TESObjectREFR*)ScriptDragon::Game::GetPlayer();
				ScriptDragon::TESNPC* pNPC = (ScriptDragon::TESNPC*)ScriptDragon::Game::GetFormById(ID_TESNPC::EncBandit00Template);
				IFormFactory* pFactory = IFormFactory::GetFactoryForType(kFormType_NPC);
				TESNPC* pNpc = (TESNPC*)pFactory->Create();
				
				pNpc->CopyFromEx((TESForm*)pNPC);
				pNpc->fullName.name = BSFixedString("Lol");

				m_pActor = (Actor*)ScriptDragon::ObjectReference::PlaceActorAtMe(pMe, (ScriptDragon::TESNPC*)pNPC, 4, NULL);
				ScriptDragon::Actor::EnableAI((ScriptDragon::CActor*)m_pActor, false);
				m_pActor = (Actor*)ScriptDragon::ObjectReference::PlaceActorAtMe(pMe, (ScriptDragon::TESNPC*)pNpc, 4, NULL);
			}
			
			SkyrimTest::~SkyrimTest()
			{
			}

			void SkyrimTest::Update()
			{
				if (m_jumped == false)
				{
					BSFixedString str("bAnimationDriven");
					bool success = m_pActor->animGraphHolder.SetVariableBool(&str, true);
					BSFixedString str2("bMotionDriven");
					success &= m_pActor->animGraphHolder.SetVariableBool(&str2, false);
					BSFixedString speedStr("Speed");
					float fSpeed = 0.0f;
					success &= m_pActor->animGraphHolder.SetVariableFloat(&speedStr, fSpeed);

					BSFixedString animStr("JumpStandingStart");
					if (m_pActor->animGraphHolder.SendAnimationEvent(&animStr) && success)
					{
						m_pActor->UpdateSkinColor();
						m_pActor->UpdateHairColor();

						m_jumped = true;
					}
				}
			}
		}
	}
}