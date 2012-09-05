#pragma once

#include "Forms.hpp"
#include "References.hpp"

namespace FreeScript
{
	void QueueNiNode(void* ptr);
	::FreeScript::TESForm* GetBaseForm(void* ptr);
	::FreeScript::TESNPC* GetNpc(::FreeScript::TESForm* ptr);
	uint32_t GetNpcFormID(::FreeScript::TESNPC* ptr);
	FreeScript::TESForm* GetWornForm(::FreeScript::Actor* ptr, uint32_t mask);
}