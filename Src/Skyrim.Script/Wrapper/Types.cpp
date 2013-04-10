#include "Stdafx.h"
#pragma unmanaged
#include "common/skyscript.h"
#pragma managed

#include "Types.h"

using namespace System;

namespace SkyrimScript
{
	namespace Wrapper
	{
		BSFixedString::BSFixedString(FreeScript::BSFixedString* ptr) : ptr((void*)ptr)
		{

		}

		BSFixedString::~BSFixedString()
		{

		}

		System::String^ BSFixedString::ToString()
		{
			return gcnew System::String(((FreeScript::BSFixedString*)ptr)->data);
		}
	}
}