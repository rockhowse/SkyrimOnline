#pragma once

#include "Forms.hpp"

namespace FreeScript
{
	void QueueNiNode(void* ptr);
	::FreeScript::TESForm* GetBaseForm(void* ptr);
	::FreeScript::TESNPC* GetNpc(::FreeScript::TESForm* ptr);
	uint32_t GetNpcFormID(::FreeScript::TESNPC* ptr);
}