#include "stdafx.h"
#include "GameObjects.h"

Game::Oblivion::TESObjectREFR::TESObjectREFR(void * ptr)
	: Game::Oblivion::TESForm(ptr)
{

}

Game::Oblivion::TESObjectREFR::~TESObjectREFR()
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