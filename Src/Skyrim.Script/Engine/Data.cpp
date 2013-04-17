#include "Stdafx.h"
#include "Data.hpp"
#include <Overlay/System.h>
#include <Overlay/Chat.h>
#include <Hook/Function.hpp>

IDirect3DDevice9* TheIDirect3DDevice9;
IDirect3D9* TheIDirect3D9;
IInputHook* TheIInputHook;

#pragma unmanaged

extern "C" __declspec(dllexport) void SetVariables(IDirect3DDevice9* pDevice, 
												   IDirect3D9* pDirect, 
												   IInputHook* pInput, 	
												   Signal<void(IDirect3DDevice9*)>* OnPresent,
												   Signal<void(IDirect3DDevice9*)>* OnReset)
{
	TheIDirect3DDevice9 = pDevice;
	TheIDirect3D9 = pDirect;
	TheIInputHook = pInput;

	Skyrim::Overlay::TheSystem = new Skyrim::Overlay::System();
	OnPresent->Add(std::bind(&Skyrim::Overlay::System::OnRender, Skyrim::Overlay::TheSystem, std::placeholders::_1));
	OnReset->Add(std::bind(&Skyrim::Overlay::System::OnLostDevice, Skyrim::Overlay::TheSystem, std::placeholders::_1));
	auto chat = new Skyrim::Overlay::Chat(Skyrim::Overlay::TheSystem->GetGui());
	chat->Show();
}