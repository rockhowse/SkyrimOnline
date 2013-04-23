#include "Stdafx.h"
#pragma unmanaged
#include <FreeScript/Forms.hpp>
#include <common/skyscript.h>
#pragma managed

#include "Forms.h"

using namespace System;
using namespace Game;

Skyrim::TESForm::TESForm(void* ptr) : Skyrim::BaseFormComponent(ptr)
{

}
Skyrim::TESForm::~TESForm()
{

}

int Skyrim::TESForm::FormID::get()
{
	return ((FreeScript::TESForm*)NativeHandle)->formID;
}

int Skyrim::TESForm::FormType::get()
{
	return ((FreeScript::TESForm*)NativeHandle)->formType;
}

int Skyrim::TESForm::Flags::get()
{
	return ((FreeScript::TESForm*)NativeHandle)->flags;
}

Skyrim::TESObjectCELL::TESObjectCELL(void* ptr) : Skyrim::TESForm(ptr)
{

}

Skyrim::TESObjectCELL::~TESObjectCELL()
{

}

Skyrim::TESObject::TESObject(void* ptr): Skyrim::TESForm(ptr)
{

}

Skyrim::TESObject::~TESObject()
{

}

Skyrim::TESBoundObject::TESBoundObject(void* ptr) : Skyrim::TESObject(ptr)
{

}

Skyrim::TESBoundObject::~TESBoundObject()
{

}

Skyrim::TESBoundAnimObject::TESBoundAnimObject(void* ptr)
	:Skyrim::TESBoundObject(ptr)
{

}

Skyrim::TESBoundAnimObject::~TESBoundAnimObject()
{

}

Skyrim::TESActorBase::TESActorBase(void* ptr)
	:TESBoundAnimObject(ptr)
{

}

Skyrim::TESActorBase::~TESActorBase()
{

}

Skyrim::TESNPC::TESNPC(void* ptr)
	:Skyrim::TESActorBase(ptr)
{

}

Skyrim::TESNPC::~TESNPC()
{

}

Skyrim::TESRace^ Skyrim::TESNPC::Race::get()
{
	auto npc = FreeScript::ActorHelper((FreeScript::Actor*)NativeHandle).GetNpc();
	return gcnew Skyrim::TESRace(npc->race.race);
}

System::UInt32 Skyrim::TESNPC::Gender::get()
{
	auto npc = FreeScript::ActorHelper((FreeScript::Actor*)NativeHandle).GetNpc();
	return npc->gender;
}

array<float>^ Skyrim::TESNPC::FaceMorphs::get()
{
	array<float>^ arr = gcnew array<float>(19);

	std::vector<float> fmorphs(19);
	auto npc = FreeScript::ActorHelper((FreeScript::Actor*)NativeHandle).GetNpc();
	FreeScript::TESNPCHelper(npc).GetFaceMorph(fmorphs);

	for(System::UInt32 i = 0; i < 19; ++i)
	{
		arr[i] = fmorphs[i];
	}

	return arr;
}

void Skyrim::TESNPC::FaceMorphs::set(array<float>^ val)
{
	if(val->Length != 19)
		throw gcnew Exception("FaceMorphs must contain 19 values.");

	std::vector<float> fmorphs(19);
	for(System::UInt32 i = 0; i < 19; ++i)
	{
		fmorphs[i] = val[i];
	}

	auto npc = FreeScript::ActorHelper((FreeScript::Actor*)NativeHandle).GetNpc();
	FreeScript::TESNPCHelper(npc).SetFaceMorph(fmorphs);
}

Skyrim::TESRace::TESRace(void* ptr) : Skyrim::TESForm(ptr)
{

}

Skyrim::TESRace::~TESRace()
{

}


