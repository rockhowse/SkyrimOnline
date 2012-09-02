#include "stdafx.h"
#include "Actor.h"
#include "skse/PapyrusActor.h"
#include "skse/PapyrusActorBase.h"
#include "FreeScript/Actor.h"
#include "FreeScript/RTTI.h"

namespace SkyrimScript
{
	uint32_t GetRace(void* pActor)
	{
		if(pActor)
		{
			TESNPC* npc = rtti_cast(FreeScript::GetBaseForm(pActor), TESForm, TESNPC);
			if(npc)
			{
				return npc->race.race->formID;
			}
		}
		return 0;
	}

	void* GetBaseForm(void* pActor)
	{
		if(pActor)
			return FreeScript::GetBaseForm(pActor);
		return nullptr;
	}

	void* ActorListAt(uint32_t pIndex)
	{
		TESForm* me;
		if(!DataHandler::GetSingleton()->unkDOBJs.GetNthItem(pIndex, me))
			me = nullptr;
		return (void*)DYNAMIC_CAST(me, TESForm, Actor);
	}

	uint32_t ActorListCount()
	{
		return DataHandler::GetSingleton()->unkDOBJs.count;
	}

	void* GetWornForm(void* pActor, uint32_t mask)
	{
		CActor* actor = (CActor*)pActor;
		if(actor)
			return papyrusActor::GetWornForm(actor,mask);
		return nullptr;
	}

	void SetName(void* pActor, const std::string& pName)
	{
		if(!pActor) return;
		TESNPC* npc = rtti_cast(FreeScript::GetBaseForm(pActor), TESForm, TESNPC);
		if(!npc) return;
		npc->fullName.name = StringCache::Ref::Ref(pName.c_str());
	}

	void QueueNiNodeUpdate(void* pActor)
	{
		FreeScript::QueueNiNode(pActor);
	}
}