#pragma once

namespace SkyrimScript
{
	TESNPC* NpcListAt(uint32_t pIndex);
	uint32_t NpcListCount();
	std::string NpcGetName(TESNPC* pThis);
	void GetFaceMorph(TESNPC* pThis, std::vector<float>* pMorphOptions);
	void SetFaceMorph(TESNPC* pThis, std::vector<float>* pMorphOptions);
}