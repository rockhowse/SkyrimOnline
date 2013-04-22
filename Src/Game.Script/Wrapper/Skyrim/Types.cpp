#include "Stdafx.h"
#pragma unmanaged
#include <common/skyscript.h>
#pragma managed

#include "Types.h"

using namespace System;
using namespace Skyrim;

Script::BSFixedString::BSFixedString(FreeScript::BSFixedString* ptr) : ptr((void*)ptr)
{

}

Script::BSFixedString::~BSFixedString()
{

}

System::String^ Script::BSFixedString::ToString()
{
	return gcnew System::String(((FreeScript::BSFixedString*)ptr)->data);
}
