#include "Stdafx.h"
#pragma unmanaged
#include <FreeScript/Components.hpp>
#include <common/skyscript.h>
#pragma managed

#include "Components.h"

using namespace System;
using namespace Game;


Skyrim::BaseFormComponent::BaseFormComponent(void* ptr) : ptr(ptr)
{

}

Skyrim::BaseFormComponent::~BaseFormComponent()
{

}

void* Skyrim::BaseFormComponent::NativeHandle::get()
{
	return ptr;
}

Skyrim::TESFullName::TESFullName(void* ptr) : Skyrim::BaseFormComponent(ptr)
{

}

Skyrim::TESFullName::~TESFullName()
{

}

Skyrim::BSFixedString^ Skyrim::TESFullName::Name::get()
{
	return gcnew Skyrim::BSFixedString(&((FreeScript::TESFullName*)NativeHandle)->name);
}

