#pragma once

#include <stdafx.h>

#include <messages/Client/GameCli_Handler.h>
#include <Engine/Controllers/SkyrimTest.h>
#include <Engine/Controllers/SkyrimHelpers.h>
#include <skyscript.h>
#include <enums.h>
#include <GameRTTI.h>
#include <mhook.h>
#include <PapyrusVM.h>
#include <GameForms.h>
#include <GameObjects.h>


SkyrimTest::SkyrimTest()
	: m_jumped(false)
{
	ScriptDragon::TESObjectREFR* pMe = (ScriptDragon::TESObjectREFR*)ScriptDragon::Game::GetPlayer();
	Actor* pActor = (Actor*)ScriptDragon::Game::GetPlayer();
	ScriptDragon::TESNPC* pNPC = (ScriptDragon::TESNPC*)pActor->baseForm;
	IFormFactory* pFactory = IFormFactory::GetFactoryForType(kFormType_NPC);
	TESNPC* pNpc = (TESNPC*)pFactory->Create();
	pNpc->CopyFromEx((TESForm*)pNPC);

	Messages::Npc serializeStruct;
	Serialize((TESNPC*)pNPC, serializeStruct);
	Deserialize(pNpc, serializeStruct);

	pNpc->fullName.name = BSFixedString("Lol");

	m_pActor = (Actor*)ScriptDragon::ObjectReference::PlaceActorAtMe(pMe, (ScriptDragon::TESNPC*)pNpc, 4, NULL);
}
			
SkyrimTest::~SkyrimTest()
{
}

void SkyrimTest::Update()
{
	Actor* pActor = (Actor*)ScriptDragon::Game::GetPlayer();

	BSFixedString str("bAnimationDriven");
	bool success = m_pActor->animGraphHolder.SetVariableBool(&str, true);
	BSFixedString str2("bMotionDriven");
	success &= m_pActor->animGraphHolder.SetVariableBool(&str2, false);
	BSFixedString str3("bInMoveState");
	m_pActor->animGraphHolder.SetVariableBool(&str3, true);

	BSFixedString directionStr("Direction");
	float dir = 0.0f;
	pActor->animGraphHolder.GetVariableFloat(&directionStr, &dir);
	m_pActor->animGraphHolder.SetVariableFloat(&directionStr, dir);

	//TheController->GetUI()->Debug()

	//if (m_jumped == false)
	{

		//BSFixedString speedStr("Speed");
		//float fSpeed = 0.0f;
		//success &= m_pActor->animGraphHolder.SetVariableFloat(&speedStr, fSpeed);

		BSFixedString animStr("MoveStart");



		if (m_pActor->animGraphHolder.SendAnimationEvent(&animStr) && success)
		{
			m_jumped = true;
		}
	}
}
