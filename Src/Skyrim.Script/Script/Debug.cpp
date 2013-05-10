#include "Stdafx.h"
#pragma managed
#include "Debug.h"
#include "../Wrapper/References.h"
#pragma unmanaged
#include "common/skyscript.h"
#pragma managed
using namespace System;


void Game::Script::Skyrim::Debug::Notification(System::String^ pstr)
{
	char* str = (char*)(void*)
		Runtime::InteropServices::Marshal::StringToHGlobalAnsi(pstr);

	::Debug::Notification(str);

	Runtime::InteropServices::Marshal::FreeHGlobal(IntPtr(str));
}

void Game::Script::Skyrim::Debug::SendAnimationEvent(::Game::IActor^ arRef, System::String^ asEventName)
{
	char* str = (char*)(void*)
		Runtime::InteropServices::Marshal::StringToHGlobalAnsi(asEventName);

	::Debug::SendAnimationEvent((FreeScript::TESObjectREFR*)((::Game::Skyrim::Actor^)arRef)->NativeHandle, str);

	Runtime::InteropServices::Marshal::FreeHGlobal(IntPtr(str));
}
