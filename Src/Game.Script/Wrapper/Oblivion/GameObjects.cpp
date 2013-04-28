#include "stdafx.h"
#include "GameObjects.h"
#include "common/plugin.h"

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
	double result;

	std::vector<unsigned char> params;
	params.push_back(2); // Param size
	params.push_back(0); // NULL byte
	params.push_back('Y'); // Axis


	if(!CallOblivionFunction("GetPos", NativeHandle, params, 1, &result))
		MessageBoxA(0,"Call returned false","",0);
	vec.X = result;

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