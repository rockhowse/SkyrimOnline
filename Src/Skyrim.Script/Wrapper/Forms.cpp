#include "Stdafx.h"
#pragma unmanaged
#include <FreeScript/Forms.hpp>
#include <common/skyscript.h>
#pragma managed

#include "Forms.h"

using namespace System;
using namespace Game;

Game::Skyrim::TESForm::TESForm(void* ptr) : Game::Skyrim::BaseFormComponent(ptr)
{

}
Game::Skyrim::TESForm::~TESForm()
{

}

int Game::Skyrim::TESForm::FormID::get()
{
	return ((FreeScript::TESForm*)NativeHandle)->formID;
}

int Game::Skyrim::TESForm::FormType::get()
{
	return ((FreeScript::TESForm*)NativeHandle)->formType;
}

int Game::Skyrim::TESForm::Flags::get()
{
	return ((FreeScript::TESForm*)NativeHandle)->flags;
}

Game::Skyrim::TESObjectCELL::TESObjectCELL(void* ptr) : Game::Skyrim::TESForm(ptr)
{

}

Game::Skyrim::TESObjectCELL::~TESObjectCELL()
{

}

Game::Skyrim::TESObject::TESObject(void* ptr): Game::Skyrim::TESForm(ptr)
{

}

Game::Skyrim::TESObject::~TESObject()
{

}

Game::Skyrim::TESBoundObject::TESBoundObject(void* ptr) : Game::Skyrim::TESObject(ptr)
{

}

Game::Skyrim::TESBoundObject::~TESBoundObject()
{

}

Game::Skyrim::TESBoundAnimObject::TESBoundAnimObject(void* ptr)
	: Game::Skyrim::TESBoundObject(ptr)
{

}

Game::Skyrim::TESBoundAnimObject::~TESBoundAnimObject()
{

}

Game::Skyrim::TESActorBase::TESActorBase(void* ptr)
	:TESBoundAnimObject(ptr)
{

}

Game::Skyrim::TESActorBase::~TESActorBase()
{

}

Game::Skyrim::TESNPC::TESNPC(void* ptr)
	:Skyrim::TESActorBase(ptr)
{

}

Game::Skyrim::TESNPC::~TESNPC()
{

}

Game::Skyrim::TESRace^ Game::Skyrim::TESNPC::Race::get()
{
	auto npc = FreeScript::ActorHelper((FreeScript::Actor*)NativeHandle).GetNpc();
	return gcnew Game::Skyrim::TESRace(npc->race.race);
}

System::UInt32 Game::Skyrim::TESNPC::Gender::get()
{
	auto npc = FreeScript::ActorHelper((FreeScript::Actor*)NativeHandle).GetNpc();
	return npc->gender;
}

array<float>^ Game::Skyrim::TESNPC::FaceMorphs::get()
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

void Game::Skyrim::TESNPC::FaceMorphs::set(array<float>^ val)
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

Game::Skyrim::TESRace::TESRace(void* ptr) : Game::Skyrim::TESForm(ptr)
{

}

Game::Skyrim::TESRace::~TESRace()
{

}


