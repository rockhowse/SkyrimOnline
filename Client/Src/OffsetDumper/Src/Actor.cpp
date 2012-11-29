#include "stdafx.h"
#include "Test.hpp"

void RunActorDump()
{
	FreeScript::Actor* player = (FreeScript::Actor*)Game::GetPlayer();
	auto npc = FreeScript::ActorHelper(player).GetNpc();

	std::vector<float> forms;
	std::vector<uint32_t> worn;

	FreeScript::QueueNiNodeUpdate(player);

	RUN_TEST(FreeScript::IFormFactory::GetFactory(61)->GetName())

	for(auto i = 0; i < 31; ++i)
	{
		auto f = FreeScript::GetWornForm(player, 1 << i);
		if(f)
			OUTPUT << std::hex << f->formID << std::endl;
	}

	for(uint32_t i = 0, size = FreeScript::TESDataHandler::GetInstance()->mNpcs.size; i != size; ++i)
	{
		RUN_TEST(TESNPCHelper(FreeScript::TESDataHandler::GetInstance()->mNpcs[i]).GetDebugName())
	}

	for(uint32_t i = 0, size = player->parentCell->childList.size; i != size; ++i)
	{
		auto actor = rtti_cast(player->parentCell->childList[i], TESObjectREFR, Actor);
		if(actor)
			RUN_TEST(player->parentCell->childList[i]->baseForm->formID)
	}

	TESNPCHelper(npc).GetFaceMorph(forms);
	RUN_TEST(forms.size())
	for(auto itor = forms.begin(); itor != forms.end(); ++itor)
	{
		OUTPUT << *itor << std::endl;
	}
	RUN_TEST(TESNPCHelper(npc).GetRaceID())

	RUN_TEST(offsetof(FreeScript::TESNPC, faceMorph))
	RUN_TEST(offsetof(FreeScript::Actor, baseForm))
	RUN_TEST(offsetof(FreeScript::TESNPC, race))
	RUN_TEST(offsetof(FreeScript::TESRaceForm, race))
	RUN_TEST(offsetof(FreeScript::TESRace, formID))

	RUN_TEST(sizeof(FreeScript::TESNPC));
	RUN_TEST(sizeof(FreeScript::TESRace));
	RUN_TEST(sizeof(FreeScript::TESNPC));
	RUN_TEST(sizeof(FreeScript::Actor));
	RUN_TEST(sizeof(FreeScript::TESObjectREFR));
	RUN_TEST(sizeof(FreeScript::TESForm));
	RUN_TEST(sizeof(FreeScript::BaseFormComponent));

}