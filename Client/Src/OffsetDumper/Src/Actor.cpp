#include "stdafx.h"
#include "Test.hpp"

void RunActorDump()
{
	FreeScript::Actor* player = (FreeScript::Actor*)Game::GetPlayer();
	auto baseForm = FreeScript::GetBaseForm(player);

	std::cout << std::hex << SkyrimScript::GetRace(player) << std::endl;
}