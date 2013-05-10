#include "stdafx.h"
#include "GameObjects.h"
#include "Script/ObscriptCaller.hpp"

#pragma managed

Game::Oblivion::TESObjectREFR::TESObjectREFR(void * ptr)
	: Game::Oblivion::TESForm(ptr)
{

}

Game::Oblivion::TESObjectREFR::~TESObjectREFR()
{

}
Microsoft::Xna::Framework::Vector3 Game::Oblivion::TESObjectREFR::Position::get()
{
	Microsoft::Xna::Framework::Vector3 vec;

	{
		ObscriptCaller caller("GetPos");
		caller.Push((const char)'X');
		vec.X = caller(NativeHandle);
	}
	{
		ObscriptCaller caller("GetPos");
		caller.Push((const char)'Y');
		vec.Y = caller(NativeHandle);
	}
	{
		ObscriptCaller caller("GetPos");
		caller.Push((const char)'Z');
		vec.Z = caller(NativeHandle);
	}

	return vec;
}

void Game::Oblivion::TESObjectREFR::Position::set(Microsoft::Xna::Framework::Vector3 vec)
{

}

Microsoft::Xna::Framework::Vector3 Game::Oblivion::TESObjectREFR::Rotation::get()
{
	Microsoft::Xna::Framework::Vector3 vec;

	return vec;
}

void Game::Oblivion::TESObjectREFR::Rotation::set(Microsoft::Xna::Framework::Vector3 vec)
{

}

Game::ITESForm^ Game::Oblivion::TESObjectREFR::BaseForm::get()
{
	double res;

	ObscriptCaller caller("GetBaseObject");
	res = caller(NativeHandle);

	return gcnew Game::Oblivion::TESForm((void*)*(UInt32*)&res);
}


Game::Oblivion::MobileObject::MobileObject(void * ptr)
	: Game::Oblivion::TESObjectREFR(ptr)
{

}

Game::Oblivion::MobileObject::~MobileObject()
{

}

Game::Oblivion::Actor::Actor(void* ptr)
	: Game::Oblivion::MobileObject(ptr)
{

}

Game::Oblivion::Actor::~Actor()
{

}

void Game::Oblivion::Actor::EnableAI(bool enabled)
{
	ObscriptCaller caller("SetActorsAI");
	if(enabled)
		caller.Push(int(1));
	else
	{
		caller.Push(int(0));
	}
	caller(NativeHandle);
}

void Game::Oblivion::Actor::EquipItem(ITESForm^ form)
{
	TESForm^ f = (TESForm^)form;

	ObscriptCaller caller("EquipItemSilent");
	caller.PushForm(f->NativeHandle);
	caller.Push(int(1));

	caller(NativeHandle);
}

void Game::Oblivion::Actor::UnequipAll()
{
	

}