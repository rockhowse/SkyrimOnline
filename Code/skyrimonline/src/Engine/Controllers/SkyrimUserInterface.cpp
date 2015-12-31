#pragma once

#include <stdafx.h>

#include <Engine/Controllers/SkyrimController.h>
#include <skyscript.h>


SkyrimUserInterface::SkyrimUserInterface()
{}

SkyrimUserInterface::~SkyrimUserInterface()
{}

void SkyrimUserInterface::Debug(const std::string& acString)
{
	ScriptDragon::Debug::Notification((char*)acString.c_str());
}
