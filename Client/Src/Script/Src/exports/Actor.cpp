#include "stdafx.h"
#include "Actor.h"
#include "skse/PapyrusActor.h"
#include "skse/PapyrusActorBase.h"
#include "FreeScript/References.hpp"
#include "FreeScript/Actor.hpp"
#include "FreeScript/RTTI.hpp"

namespace SkyrimScript
{
	uint32_t GetRace(FreeScript::Actor* pActor)
	{
		if(pActor)
		{
			::FreeScript::TESNPC* npc = rtti_cast(FreeScript::GetBaseForm(pActor), TESForm, TESNPC);
			if(npc)
			{
				return npc->race.race->formID;
			}
		}
		return 0;
	}

	FreeScript::TESForm* GetBaseForm(FreeScript::Actor* pActor)
	{
		if(pActor)
			return FreeScript::GetBaseForm(pActor);
		return nullptr;
	}

	void* ActorListAt(uint32_t pIndex)
	{
		TESForm* me;
		me = nullptr;
		return nullptr;
	}

	uint32_t ActorListCount()
	{
		return 0;
	}

	FreeScript::TESForm* GetWornForm(FreeScript::Actor* pActor, uint32_t mask)
	{
		if(pActor)
			return (FreeScript::TESForm*)papyrusActor::GetWornForm((Actor*)pActor,mask);
		return nullptr;
	}

	void SetName(FreeScript::Actor* pActor, const std::string& pName)
	{
		if(!pActor) return;
		FreeScript::TESNPC* npc = rtti_cast(FreeScript::GetBaseForm(pActor), TESForm, TESNPC);
		if(!npc) return;
		//npc->fullName.name = StringCache::Ref::Ref(pName.c_str());
	}

	void QueueNiNodeUpdate(FreeScript::Actor* pActor)
	{
		FreeScript::QueueNiNode(pActor);
	}
}