#include "stdafx.h"
#include "Actor.hpp"

namespace FreeScript
{
	void QueueNiNode(void* ptr)
	{
		((void(__thiscall*)(CActor*))0x0072CD80)((CActor*)ptr);
	}

	::FreeScript::TESForm* GetBaseForm(void* ptr)
	{
		return (TESForm*)((char*)ptr + 0x24);
	}

	::FreeScript::TESNPC* GetNpc(::FreeScript::TESForm* ptr)
	{
		return (::FreeScript::TESNPC*)((char*)ptr + 0xC4);
	}

	uint32_t GetNpcFormID(::FreeScript::TESNPC* ptr)
	{
		return ptr->race.race->formID;
	}
}