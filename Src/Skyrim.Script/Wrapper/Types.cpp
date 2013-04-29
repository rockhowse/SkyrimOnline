#include "Stdafx.h"
#pragma unmanaged
#include <common/skyscript.h>
#pragma managed

#include "Types.h"

using namespace System;
using namespace Game;

Game::Skyrim::BSFixedString::BSFixedString(FreeScript::BSFixedString* ptr) : ptr((void*)ptr)
{

}

Game::Skyrim::BSFixedString::~BSFixedString()
{

}

System::String^ Game::Skyrim::BSFixedString::ToString()
{
	return gcnew System::String(((FreeScript::BSFixedString*)ptr)->data);
}
