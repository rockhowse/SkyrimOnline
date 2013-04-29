#include "Stdafx.h"
#include "Chat.h"
#include <Overlay/Chat.h>
#include <Overlay/System.h>
#pragma managed

#include "../../Hook/clix.h"
#include < vcclr.h >

using namespace Game;

delegate void Input_Handler(const std::string& pStr);

void inputHandler(gcroot<Overlay::Chat^> This, const std::string& pStr)
{
	This->_inputHandle(pStr);
}

Overlay::Chat::Chat()
{
	NativeHandle = new Skyrim::Overlay::Chat(Skyrim::Overlay::TheSystem->GetGui());
	((Skyrim::Overlay::Chat*)NativeHandle)->OnInput.Add(std::bind(inputHandler, gcroot<Overlay::Chat^>(this), std::placeholders::_1));
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

void Overlay::Chat::_inputHandle(const std::string& pStr)
{
	OnInput(clix::marshalString<clix::E_UTF8>(pStr));
}