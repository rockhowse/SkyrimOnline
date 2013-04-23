#include "Stdafx.h"
#pragma unmanaged
#include <FreeScript/References.hpp>
#include <common/skyscript.h>
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
	return gcnew Script::TESForm(((FreeScript::TESObjectREFR*)NativeHandle)->baseForm);
}

Microsoft::Xna::Framework::Vector3 Script::TESObjectREFR::Position::get()
{
	Microsoft::Xna::Framework::Vector3 vec;
	vec.X = ((FreeScript::TESObjectREFR*)ptr)->pos.X;
	vec.Y = ((FreeScript::TESObjectREFR*)ptr)->pos.Y;
	vec.Z = ((FreeScript::TESObjectREFR*)ptr)->pos.Z;
	return vec;
}

void Script::TESObjectREFR::Position::set(Microsoft::Xna::Framework::Vector3 vec)
{
	((FreeScript::TESObjectREFR*)ptr)->pos.X = vec.X;
	((FreeScript::TESObjectREFR*)ptr)->pos.Y = vec.Y;
	((FreeScript::TESObjectREFR*)ptr)->pos.Z = vec.Z;
}

Microsoft::Xna::Framework::Vector3 Script::TESObjectREFR::Rotation::get()
{
	Microsoft::Xna::Framework::Vector3 vec;
	vec.X = ((FreeScript::TESObjectREFR*)ptr)->rot.X;
	vec.Y = ((FreeScript::TESObjectREFR*)ptr)->rot.Y;
	vec.Z = ((FreeScript::TESObjectREFR*)ptr)->rot.Z;
	return vec;
}

void Script::TESObjectREFR::Rotation::set(Microsoft::Xna::Framework::Vector3 vec)
{
	((FreeScript::TESObjectREFR*)ptr)->rot.X = vec.X;
	((FreeScript::TESObjectREFR*)ptr)->rot.Y = vec.Y;
	((FreeScript::TESObjectREFR*)ptr)->rot.Z = vec.Z;
}


Script::Actor::Actor(void* ptr) : Script::TESObjectREFR(ptr)
{

}

Script::Actor::~Actor()
{

}

void Script::Actor::QueueNiNodeUpdate()
{
	FreeScript::QueueNiNodeUpdate((FreeScript::Actor*)NativeHandle);
}

void Script::Actor::UnequipAll()
{
	SActor::UnequipAll((FreeScript::Actor*)NativeHandle);
}

Script::TESNPC^ Script::Actor::BaseNpc::get()
{
	return gcnew Script::TESNPC(FreeScript::ActorHelper((FreeScript::Actor*)NativeHandle).GetNpc());
}

bool Script::Actor::Dead::get()
{
	return SActor::IsDead((FreeScript::Actor*)NativeHandle);
}

System::UInt32 Script::Actor::Level::get()
{
	return SActor::GetLevel((FreeScript::Actor*)NativeHandle);
}

Script::TESForm^ Script::Actor::GetWornForm(System::UInt32 id)
{
	if(id > 14)
		throw gcnew Exception("The worn forms are in the following range [0, 14]");
	return gcnew Script::TESForm((void*)FreeScript::GetWornForm((FreeScript::Actor*)NativeHandle, 1 << id));
}

void Script::Actor::EquipItem(Script::TESForm^ form)
{
	::ObjectReference::AddItem(rtti_cast(ptr, Actor, TESObjectREFR), (FreeScript::TESForm*)form->NativeHandle, 1, true);
	SActor::EquipItem((FreeScript::Actor*)ptr, (FreeScript::TESForm*)form->NativeHandle, true, false);
}