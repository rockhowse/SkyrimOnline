#include "Stdafx.h"
#include "Data.hpp"
#include <Overlay/System.h>
#include <Overlay/Chat.h>
#include <Hook/Function.hpp>
#include <Wrapper/Input.hpp>

IDirect3DDevice9* TheIDirect3DDevice9;
IDirect3D9* TheIDirect3D9;
IInputHook* TheIInputHook;
InputListener* TheInputListener;

#pragma managed

using namespace Game;

struct UnmanagedInputListener : public InputListener
{
	virtual void OnPress(BYTE code)
	{
		Event^ ev = gcnew KeyboardEvent(code, true); 
		Game::Input::Push(ev);
	}
	virtual void OnRelease(BYTE code)
	{
		Event^ ev = gcnew KeyboardEvent(code, false); 
		Game::Input::Push(ev);
	}
	virtual void OnMousePress(BYTE code) 
	{
		Event^ ev = gcnew MouseEvent(code, true); 
		Game::Input::Push(ev);
	}
	virtual void OnMouseRelease(BYTE code) 
	{
		Event^ ev = gcnew MouseEvent(code, false); 
		Game::Input::Push(ev);
	}
	virtual void OnMouseMove(unsigned int x, unsigned int y, unsigned int z)
	{
		Event^ ev = gcnew MousePositionEvent(x,y,z); 
		Game::Input::Push(ev);
	}
};

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
	TheInputListener = new UnmanagedInputListener;

	TheIInputHook->SetListener(TheInputListener);

	Skyrim::Overlay::TheSystem = new Skyrim::Overlay::System();

	OnPresent->Add(std::bind(&Skyrim::Overlay::System::OnRender, Skyrim::Overlay::TheSystem, std::placeholders::_1));
	OnReset->Add(std::bind(&Skyrim::Overlay::System::OnLostDevice, Skyrim::Overlay::TheSystem, std::placeholders::_1));
}