#include "stdafx.h"
#include "Oblivion.hpp"
#include "Plugins.hpp"

#pragma unmanaged

typedef int (__thiscall* tUpdate)(void*);
tUpdate oUpdate;

typedef void (*tSetVariables)(IDirect3DDevice9* pDevice, IDirect3D9* pDirect, IInputHook* pInput, Signal<void(IDirect3DDevice9*)>*,Signal<void(IDirect3DDevice9*)>*);
extern tSetVariables SetVariables;

int __fastcall Update(void* pthis, void* fastcall)
{
	static bool init = false;
	if(init == false)
	{
		auto mod = LoadLibraryA("Game.Script.dll");

		SetVariables = (tSetVariables)GetProcAddress(mod, "SetVariables");

		IDirect3D9* pDevice;
		myIDirect3DDevice9::GetInstance()->GetDirect3D(&pDevice);
		SetVariables(myIDirect3DDevice9::GetInstance()->GetDevice(), pDevice, TheIInputHook, 
			&myIDirect3DDevice9::GetInstance()->OnPresent,
			&myIDirect3DDevice9::GetInstance()->OnReset);
			
		init = true;
	}

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


