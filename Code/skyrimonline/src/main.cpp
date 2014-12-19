#include <iostream>
#include "World.h"

#include "plugin.h"
#include "skyscript.h"

World* g_pWorld = nullptr;

typedef void(*tInitializeGame)(void);
tInitializeGame InitializeGame;

extern "C" __declspec(dllexport) void main()
{
	EnetServer::Initialize();

	g_pWorld = new World;

	auto GameModule = GetModuleHandleA("Game.Module.dll");

	if (!GameModule)
		GameModule = LoadLibraryA("Game.Module.dll");

	InitializeGame = (tInitializeGame)GetProcAddress(GameModule, "InitializeGame");

	while (true)
	{
		g_pWorld->Update();
		Wait(0);
	}
}
