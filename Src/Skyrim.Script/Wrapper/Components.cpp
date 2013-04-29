#include "Stdafx.h"
#pragma unmanaged
#include <FreeScript/Components.hpp>
#include <common/skyscript.h>
#pragma managed

#include "Components.h"

using namespace System;
using namespace Game;


Game::Skyrim::BaseFormComponent::BaseFormComponent(void* ptr) : ptr(ptr)
{

}

Game::Skyrim::BaseFormComponent::~BaseFormComponent()
{

}

void* Game::Skyrim::BaseFormComponent::NativeHandle::get()
{
	return ptr;
}

Game::Skyrim::TESFullName::TESFullName(void* ptr) : Game::Skyrim::BaseFormComponent(ptr)
{

}

Game::Skyrim::TESFullName::~TESFullName()
{

}

Game::Skyrim::BSFixedString^ Game::Skyrim::TESFullName::Name::get()
{
	return gcnew Game::Skyrim::BSFixedString(&((FreeScript::TESFullName*)NativeHandle)->name);
}

