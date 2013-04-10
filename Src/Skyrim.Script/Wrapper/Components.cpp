#include "Stdafx.h"
#pragma unmanaged
#include <FreeScript/Components.hpp>
#include "common/skyscript.h"
#pragma managed

#include "Components.h"

using namespace System;
using namespace Skyrim::Script;


Wrapper::BaseFormComponent::BaseFormComponent(void* ptr) : ptr(ptr)
{

}

Wrapper::BaseFormComponent::~BaseFormComponent()
{

}

Wrapper::TESFullName::TESFullName(void* ptr) : BaseFormComponent(ptr)
{

}

Wrapper::TESFullName::~TESFullName()
{

}

Wrapper::BSFixedString^ Wrapper::TESFullName::Name::get()
{
	return gcnew Wrapper::BSFixedString(&((FreeScript::TESFullName*)ptr)->name);
}

