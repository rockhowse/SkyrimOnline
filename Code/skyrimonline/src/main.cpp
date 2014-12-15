#include <iostream>
#include "World.h"

#include "plugin.h"
#include "skyscript.h"

World* g_pWorld = nullptr;

extern "C" __declspec(dllexport) void main()
{
	EnetServer::Initialize();

	g_pWorld = new World;

	while (true)
	{
		g_pWorld->Update();
		Wait(0);
	}
}
