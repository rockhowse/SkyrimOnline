#include <iostream>

#include <plugin.h>
#include <skyscript.h>

#include <Engine/Game.h>

extern "C" __declspec(dllexport) void main()
{
	Logic::Engine::InitializeGame();

	while (true)
	{
		Logic::Engine::Update();
		ScriptDragon::Wait(0);
	}
}
