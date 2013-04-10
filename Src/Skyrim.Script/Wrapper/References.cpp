#include "Stdafx.h"
#pragma unmanaged
#include <FreeScript/References.hpp>
#include "common/skyscript.h"
#pragma managed

#include "References.h"

using namespace System;
using namespace Skyrim::Script;


Wrapper::TESObjectREFR::TESObjectREFR(void* ptr) : Wrapper::TESForm(ptr)
{

}

Wrapper::TESObjectREFR::~TESObjectREFR()
{

}

Wrapper::TESForm^ Wrapper::TESObjectREFR::BaseForm::get()
{
	return gcnew Wrapper::TESForm(((FreeScript::TESObjectREFR*)ptr)->baseForm);
}

Wrapper::Actor::Actor(void* ptr) : Wrapper::TESObjectREFR(ptr)
{

}

Wrapper::Actor::~Actor()
{

}

