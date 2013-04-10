#include "Stdafx.h"
#pragma unmanaged
#include <FreeScript/Components.hpp>
#include "common/skyscript.h"
#pragma managed

#include "Components.h"

using namespace System;

namespace SkyrimScript
{
	namespace Wrapper
	{
		BaseFormComponent::BaseFormComponent(void* ptr) : ptr(ptr)
		{

		}

		BaseFormComponent::~BaseFormComponent()
		{

		}

		TESFullName::TESFullName(void* ptr) : BaseFormComponent(ptr)
		{

		}

		TESFullName::~TESFullName()
		{

		}

		Wrapper::BSFixedString^ TESFullName::Name::get()
		{
			return gcnew Wrapper::BSFixedString(&((FreeScript::TESFullName*)ptr)->name);
		}
	}
}