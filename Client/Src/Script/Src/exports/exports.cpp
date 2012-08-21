#include "stdafx.h"
#include "Exports.h"
#include "skse/PapyrusActor.h"
#include "skse/PapyrusActorBase.h"

BOOL APIENTRY DllMain(HMODULE hModule, DWORD fdwReason, LPVOID lpReserved)
{
    return TRUE;
}

namespace SkyrimScript
{
	void* ProxyDuplicate(void* pThis, void* pCopy)
	{
		TESForm* me = (TESForm*)pThis;
		TESForm* copy = (TESForm*)pCopy;
		me->CopyFrom(copy);

		me->Init();
		me->InitItem();

		return me;
	}
}
