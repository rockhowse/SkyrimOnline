#include "Stdafx.h"
#include "Chat.h"
#include <Overlay/Chat.h>
#include <Overlay/System.h>
#include < vcclr.h >

using namespace Game;

Overlay::Chat::Chat()
{
	NativeHandle = new Skyrim::Overlay::Chat(Skyrim::Overlay::TheSystem->GetGui());
}

Overlay::Chat::~Chat()
{
	delete (Skyrim::Overlay::Chat*)NativeHandle;
}

void Overlay::Chat::Log(System::String^ pStr)
{
	pin_ptr<const wchar_t> wchstr = PtrToStringChars(pStr);
	((Skyrim::Overlay::Chat*)NativeHandle)->Log((wchar_t*)wchstr);
}

bool Overlay::Chat::Visible::get()
{
	if(NativeHandle)
		return ((Skyrim::Overlay::Chat*)NativeHandle)->IsVisible();
	return false;
}

void Overlay::Chat::Visible::set(bool pVisible)
{
	if(NativeHandle)
		return ((Skyrim::Overlay::Chat*)NativeHandle)->SetVisible(pVisible);
}