#pragma once

#include "Forms.hpp"
#include "References.hpp"

namespace FreeScript
{
	void QueueNiNodeUpdate(FreeScript::Actor* ptr);
	FreeScript::TESForm* GetWornForm(::FreeScript::Actor* ptr, uint32_t mask);
	void SetName(FreeScript::Actor* pActor, const std::string& pName);
}