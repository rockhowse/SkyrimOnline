#pragma once

#include "FreeScript/References.hpp"

namespace SkyrimScript
{
	uint32_t GetRace(FreeScript::Actor* pActor);
	FreeScript::TESForm* GetBaseForm(FreeScript::Actor* pActor);
	void* ActorListAt(uint32_t pIndex);
	uint32_t ActorListCount();
	FreeScript::TESForm* GetWornForm(FreeScript::Actor* pActor, uint32_t mask);
	void SetName(FreeScript::Actor* pActor, const std::string& pName);
	void QueueNiNodeUpdate(FreeScript::Actor* pActor);
}