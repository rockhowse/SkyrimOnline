#include <iostream>
#include "BoostManager.h"
#include "World.h"

#include "plugin.h"
#include "skyscript.h"

World* g_pWorld = nullptr;

extern "C" __declspec(dllexport) void main()
{
	BoostManager::Setup(1);

	g_pWorld = new World;
	while (true)
	{
		g_pWorld->Update();
		Wait(0);
	}

	BoostManager::Destroy();
}
