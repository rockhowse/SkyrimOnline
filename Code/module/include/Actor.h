#pragma once

#include "Forms.h"
#include "References.h"
#include <string>
#include <cstdint>

namespace Skyrim
{
	void QueueNiNodeUpdate(Skyrim::Actor* ptr);
	Skyrim::TESForm* GetWornForm(::Skyrim::Actor* ptr, uint32_t mask);
	void SetName(Skyrim::Actor* pActor, const std::string& pName);

	::Skyrim::Actor* GetPlayer();
}