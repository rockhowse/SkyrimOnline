#include "stdafx.h"
#include "Actor.h"

namespace FreeScript
{
	void QueueNiNode(void* ptr)
	{
		((void(__thiscall*)(CActor*))0x0072CD80)((CActor*)ptr);
	}

	TESForm* GetBaseForm(void* ptr)
	{
		return (TESForm*)((char*)ptr + 0x24);
	}
}