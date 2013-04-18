#include "Stdafx.h"
#pragma unmanaged
#include <FreeScript/References.hpp>
#include "common/skyscript.h"
#pragma managed

#include "References.h"

using namespace System;
using namespace Skyrim;


Script::TESObjectREFR::TESObjectREFR(void* ptr) : Script::TESForm(ptr)
{

}

Script::TESObjectREFR::~TESObjectREFR()
{

}

Script::TESForm^ Script::TESObjectREFR::BaseForm::get()
{
	return gcnew Script::TESForm(((FreeScript::TESObjectREFR*)ptr)->baseForm);
}

Script::Actor::Actor(void* ptr) : Script::TESObjectREFR(ptr)
{

}

Script::Actor::~Actor()
{

}

Script::TESNPC^ Script::Actor::BaseNpc::get()
{
	return gcnew Script::TESNPC(FreeScript::ActorHelper((FreeScript::Actor*)ptr).GetNpc());
}
