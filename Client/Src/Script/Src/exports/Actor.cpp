#include "stdafx.h"
#include "Actor.h"
#include "skse/PapyrusActor.h"
#include "skse/PapyrusActorBase.h"

namespace SkyrimScript
{
	uint32_t GetRace(void* pActor)
	{
		CActor* actor = (CActor*)pActor;
		if(actor)
		{
			TESNPC* npc = DYNAMIC_CAST(actor->baseForm, TESForm, TESNPC);
			if(npc)
			{
				return npc->race.race->formID;
			}
		}
		return 0;
	}

	void* GetBaseForm(void* pActor)
	{
		CActor* actor = (CActor*)pActor;
		if(actor)
			return actor->baseForm;
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
		CActor* actor = (CActor*)pActor;
		if(!actor) return;
		TESNPC* npc = DYNAMIC_CAST(actor->baseForm, TESForm, TESNPC);
		if(!npc) return;
		npc->fullName.name = StringCache::Ref::Ref(pName.c_str());
	}

	void QueueNiNodeUpdate(void* pActor)
	{
		papyrusActor::QueueNiNodeUpdate((CActor*)pActor);
	}
}