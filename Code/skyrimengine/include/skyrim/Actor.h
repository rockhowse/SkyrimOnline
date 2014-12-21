#pragma once

#include "SkyrimPrefix.h"
#include "Forms.h"
#include "References.h"
#include <string>
#include <cstdint>

namespace Skyrim
{
	SKYRIM_API void QueueNiNodeUpdate(Skyrim::Actor* ptr);
	SKYRIM_API Skyrim::TESForm* GetWornForm(::Skyrim::Actor* ptr, uint32_t mask);
	SKYRIM_API void SetName(Skyrim::Actor* pActor, const std::string& pName);
	SKYRIM_API ::Skyrim::Actor* GetPlayer();
}