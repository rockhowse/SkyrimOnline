#include "Stdafx.h"
#pragma unmanaged
#include "common/skyscript.h"
#pragma managed

#include "Types.h"

using namespace System;
using namespace Skyrim::Script;

Wrapper::BSFixedString::BSFixedString(FreeScript::BSFixedString* ptr) : ptr((void*)ptr)
{

}

Wrapper::BSFixedString::~BSFixedString()
{

}

System::String^ Wrapper::BSFixedString::ToString()
{
	return gcnew System::String(((FreeScript::BSFixedString*)ptr)->data);
}
