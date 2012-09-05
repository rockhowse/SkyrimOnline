#include "stdafx.h"
#include "FreeScript/Forms.hpp"

namespace SkyrimScript
{
	FreeScript::TESNPC* NpcListAt(uint32_t pIndex)
	{
		TESNPC* me;
		me = nullptr;
		return nullptr;
	}

	uint32_t NpcListCount()
	{
		return 0;
	}

	std::string NpcGetName(FreeScript::TESNPC* pThis)
	{
		if(pThis)
			return std::to_string((uint64_t)pThis->formID) + std::string(" ") + std::string(pThis->fullName.name);
		return "";
	}

	void GetFaceMorph(FreeScript::TESNPC* pThis, std::vector<float>* pMorphOptions)
	{
		if(pMorphOptions != nullptr)
		{
			pMorphOptions->clear();
			for( auto i=0; i < pThis->faceMorph->OptionCount; ++i )
			{
				pMorphOptions->push_back(pThis->faceMorph->option[i]);
			}
		}
	}

	void SetFaceMorph(FreeScript::TESNPC* pThis, std::vector<float>* pMorphOptions)
	{
		if(pMorphOptions != nullptr)
		{
			for(uint32_t i = 0; i < pMorphOptions->size(); ++i)
					pThis->faceMorph->option[i] = pMorphOptions->at(i);
		}
	}
}