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
				f << oss.str() << std::endl;

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
				char inplaceStr[sizeof(BSFixedString)];
				BSFixedString str("bMotionDriven");
				//ScriptDragon::ObjectReference::SetAnimationVariableBool((ScriptDragon::TESObjectREFR*)m_pActor, "bMotionDriven", false);
				
				UInt8 ret = 0;
				if (m_pActor->animGraphHolder.GetVariableBool(&str, &ret))
				{
					ScriptDragon::Debug::Notification("Motion driven");
				}
				//ScriptDragon::ObjectReference::GetAnimationVariableBool((ScriptDragon::TESObjectREFR*)m_pActor, "bMotionDriven:Animation");
				ScriptDragon::ExecuteConsoleCommand("sae SprintStart", (HANDLE)m_pActor);
				//ScriptDragon::Debug::SendAnimationEvent((ScriptDragon::TESObjectREFR*)DYNAMIC_CAST(m_pActor, Actor, TESObjectREFR), "IdleForceDefaultState");
			}
		}
	}
}