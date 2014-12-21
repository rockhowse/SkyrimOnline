#include <iostream>

#include "plugin.h"
#include "skyscript.h"

typedef void(*tInitializeGame)(void);
typedef void(*tUpdate)(void);
tInitializeGame InitializeGame;
tUpdate Update;

extern "C" __declspec(dllexport) void main()
{
	auto GameModule = GetModuleHandleA("Logic.dll");

	if (!GameModule)
		GameModule = LoadLibraryA("Logic.dll");

	InitializeGame = (tInitializeGame)GetProcAddress(GameModule, "InitializeGame");
	Update = (tUpdate)GetProcAddress(GameModule, "Update");
	InitializeGame();

	while (true)
	{
		Update();
		Wait(0);
	}
}
