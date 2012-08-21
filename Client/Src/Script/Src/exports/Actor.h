#pragma once

namespace SkyrimScript
{
	uint32_t GetRace(void* pActor);
	void* GetBaseForm(void* pActor);
	void* ActorListAt(uint32_t pIndex);
	uint32_t ActorListCount();
	void* GetWornForm(void* pActor, uint32_t mask);
	void SetName(void* pActor, const std::string& pName);
	void QueueNiNodeUpdate(void* pActor);
}