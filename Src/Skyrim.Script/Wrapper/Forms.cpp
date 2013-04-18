#include "Stdafx.h"
#pragma unmanaged
#include <FreeScript/Forms.hpp>
#include "common/skyscript.h"
#pragma managed

#include "Forms.h"

using namespace System;
using namespace Skyrim;

Script::TESForm::TESForm(void* ptr) : Script::BaseFormComponent(ptr)
{

}
Script::TESForm::~TESForm()
{

}

int Script::TESForm::FormID::get()
{
	return ((FreeScript::TESForm*)ptr)->formID;
}

int Script::TESForm::FormType::get()
{
	return ((FreeScript::TESForm*)ptr)->formType;
}

int Script::TESForm::Flags::get()
{
	return ((FreeScript::TESForm*)ptr)->flags;
}

Script::TESObjectCELL::TESObjectCELL(void* ptr) : Script::TESForm(ptr)
{

}

Script::TESObjectCELL::~TESObjectCELL()
{

}

Script::TESObject::TESObject(void* ptr): Script::TESForm(ptr)
{

}

Script::TESObject::~TESObject()
{

}

Script::TESBoundObject::TESBoundObject(void* ptr) : Script::TESObject(ptr)
{

}

Script::TESBoundObject::~TESBoundObject()
{

}

Script::TESBoundAnimObject::TESBoundAnimObject(void* ptr)
	:Script::TESBoundObject(ptr)
{

}

Script::TESBoundAnimObject::~TESBoundAnimObject()
{

}

Script::TESActorBase::TESActorBase(void* ptr)
	:TESBoundAnimObject(ptr)
{

}

Script::TESActorBase::~TESActorBase()
{

}

Script::TESNPC::TESNPC(void* ptr)
	:TESActorBase(ptr)
{

}

Script::TESNPC::~TESNPC()
{

}

Script::TESRace^ Script::TESNPC::Race::get()
{
	auto npc = FreeScript::ActorHelper((FreeScript::Actor*)ptr).GetNpc();
	return gcnew Script::TESRace(npc->race.race);
}

UInt32 Script::TESNPC::Gender::get()
{
	auto npc = FreeScript::ActorHelper((FreeScript::Actor*)ptr).GetNpc();
	return npc->gender;
}

array<float>^ Script::TESNPC::FaceMorphs::get()
{
	array<float>^ arr = gcnew array<float>(19);

	std::vector<float> fmorphs(19);
	auto npc = FreeScript::ActorHelper((FreeScript::Actor*)ptr).GetNpc();
	FreeScript::TESNPCHelper(npc).GetFaceMorph(fmorphs);

	for(UInt32 i = 0; i < 19; ++i)
	{
		arr[i] = fmorphs[i];
	}

	return arr;
}

void Script::TESNPC::FaceMorphs::set(array<float>^ val)
{
	if(val->Length != 19)
		throw gcnew Exception("FaceMorphs must contain 19 values.");

	std::vector<float> fmorphs(19);
	for(UInt32 i = 0; i < 19; ++i)
	{
		fmorphs[i] = val[i];
	}

	auto npc = FreeScript::ActorHelper((FreeScript::Actor*)ptr).GetNpc();
	FreeScript::TESNPCHelper(npc).SetFaceMorph(fmorphs);
}

Script::TESRace::TESRace(void* ptr) : Script::TESForm(ptr)
{

}

Script::TESRace::~TESRace()
{

}


