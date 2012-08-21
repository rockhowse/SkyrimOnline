#include "stdafx.h"
#include "skse/PapyrusActor.h"
#include "skse/PapyrusActorBase.h"

namespace SkyrimScript
{
	TESNPC* NpcListAt(uint32_t pIndex)
	{
		TESNPC* me;
		if(!DataHandler::GetSingleton()->npcs.GetNthItem(pIndex, me))
			me = nullptr;
		return me;
	}

	uint32_t NpcListCount()
	{
		return DataHandler::GetSingleton()->npcs.count;
	}

	std::string NpcGetName(TESNPC* pThis)
	{
		TESNPC* me = (TESNPC*)pThis;
		if(me)
			return std::to_string((uint64_t)me->formID) + std::string(" ") + std::string(me->fullName.name.data);
		return "";
	}

	void GetFaceMorph(TESNPC* pThis, std::vector<float>* pMorphOptions)
	{
		TESNPC* me = (TESNPC*)pThis;
		if(pMorphOptions != nullptr)
		{
			pMorphOptions->clear();
			for( auto i=0; i < me->faceMorph->kNumOptions; ++i )
			{
				pMorphOptions->push_back(me->faceMorph->option[i]);
			}
		}
	}

	void SetFaceMorph(TESNPC* pThis, std::vector<float>* pMorphOptions)
	{
		TESNPC* me = (TESNPC*)pThis;
		if(pMorphOptions != nullptr)
		{
			for(uint32_t i = 0; i < pMorphOptions->size(); ++i)
				papyrusActorBase::SetFaceMorph(me, pMorphOptions->at(i), i);
		}
	}
}