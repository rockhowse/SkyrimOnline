#pragma once

#include <stdafx.h>

#include <Engine/Controllers/SkyrimTest.h>
#include <skyscript.h>
#include <enums.h>
#include <GameRTTI.h>
#include <mhook.h>
#include <PapyrusVM.h>

namespace Logic
{
	namespace Engine
	{
		namespace Controllers
		{
			typedef int(__thiscall *tGetVariable)(void*, BSFixedString*, uint8_t*);
			tGetVariable GetVariable_real = (tGetVariable)0x06A7E50;

			std::ofstream f("test.log", std::ios::trunc);

			int __fastcall sub_902AE0(void* pThis, void* unk, BSFixedString* apVarName, uint8_t* e)
			{
				std::ostringstream oss;
				oss << apVarName->data << " ";
				
				int cache = GetVariable_real(pThis, apVarName, e);

				oss << (int)*e;
				//f << oss.str() << std::endl;

				return cache;
			}

			SkyrimTest::SkyrimTest()
			{
				Mhook_SetHook((PVOID*)&GetVariable_real, sub_902AE0);

				ScriptDragon::TESObjectREFR* pMe = (ScriptDragon::TESObjectREFR*)ScriptDragon::Game::GetPlayer();
				ScriptDragon::TESNPC* pNPC = (ScriptDragon::TESNPC*)ScriptDragon::Game::GetFormById(ID_TESNPC::EncBandit00Template);

				m_pActor = (Actor*)ScriptDragon::ObjectReference::PlaceActorAtMe(pMe, pNPC, 4, NULL);		
			}
			
			SkyrimTest::~SkyrimTest()
			{
			}

			void SkyrimTest::Update()
			{
				BSFixedString str("bAnimationDriven");
				bool success = m_pActor->animGraphHolder.SetVariableBool(&str, true);
				BSFixedString str2("bMotionDriven");
				success = m_pActor->animGraphHolder.SetVariableBool(&str2, false);
				BSFixedString speedStr("Speed");
				float fSpeed = 80.0f;
				m_pActor->animGraphHolder.SetVariableFloat(&speedStr, fSpeed);

				BSFixedString animStr("MoveStart");
				m_pActor->animGraphHolder.SendAnimationEvent(&animStr);
			}
		}
	}
}