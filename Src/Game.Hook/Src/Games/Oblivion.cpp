#include "stdafx.h"
#include "Oblivion.hpp"
#include "Plugins.hpp"
#include "Common.hpp"

#pragma unmanaged

typedef int (__thiscall* tUpdate)(void*);
tUpdate oUpdate;


int __fastcall Update(void* pthis, void* fastcall)
{
	SetGameScriptVariables();

	GetInstance()->Run();

	return oUpdate(pthis);
}

void InstallOblivion()
{
	/*
	 * Hook CreateThread and Load scriptdragon once we are sure that the unpacker is finished AKA once VMInitThread is created
	 */
	oUpdate = (tUpdate)DetourFunction((PBYTE)0x40D800, (PBYTE)Update);
}


