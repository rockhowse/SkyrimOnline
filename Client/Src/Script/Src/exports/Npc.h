#pragma once

#include "../FreeScript/Forms.hpp"

namespace SkyrimScript
{
	FreeScript::TESNPC* NpcListAt(uint32_t pIndex);
	uint32_t NpcListCount();
	std::string NpcGetName(FreeScript::TESNPC* pThis);
	void GetFaceMorph(FreeScript::TESNPC* pThis, std::vector<float>* pMorphOptions);
	void SetFaceMorph(FreeScript::TESNPC* pThis, std::vector<float>* pMorphOptions);
}