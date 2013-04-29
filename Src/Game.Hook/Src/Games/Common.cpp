#include "Stdafx.h"
#include "Common.hpp"

typedef void (*tSetVariables)(IDirect3DDevice9* pDevice, IDirect3D9* pDirect, IInputHook* pInput, Signal<void(IDirect3DDevice9*)>*,Signal<void(IDirect3DDevice9*)>*);
tSetVariables SetVariables;

void SetGameScriptVariables(bool pForce)
{
	static bool init = false;

	if(!init || pForce)
	{
		init = true;

		auto mod = GetModuleHandle("Game.Script.dll");

		SetVariables = (tSetVariables)GetProcAddress(mod, "SetVariables");

		IDirect3D9* pDevice;
		myIDirect3DDevice9::GetInstance()->GetDirect3D(&pDevice);
		SetVariables(myIDirect3DDevice9::GetInstance()->GetDevice(), pDevice, TheIInputHook, 
			&myIDirect3DDevice9::GetInstance()->OnPresent,
			&myIDirect3DDevice9::GetInstance()->OnReset);
	}
}