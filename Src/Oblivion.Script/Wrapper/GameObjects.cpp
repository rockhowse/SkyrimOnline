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