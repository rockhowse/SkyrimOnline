#include "Stdafx.h"
#pragma unmanaged
#include <FreeScript/Components.hpp>
#include "common/skyscript.h"
#pragma managed

#include "Components.h"

using namespace System;
using namespace Skyrim;


Script::BaseFormComponent::BaseFormComponent(void* ptr) : ptr(ptr)
{

}

Script::BaseFormComponent::~BaseFormComponent()
{

}

Script::TESFullName::TESFullName(void* ptr) : Script::BaseFormComponent(ptr)
{

}

Script::TESFullName::~TESFullName()
{

}

Script::BSFixedString^ Script::TESFullName::Name::get()
{
	return gcnew Script::BSFixedString(&((FreeScript::TESFullName*)ptr)->name);
}

