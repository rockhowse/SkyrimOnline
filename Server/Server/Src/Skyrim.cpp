#define _CRT_SECURE_NO_WARNINGS

#include <Logic/World.h>
#include <System/Log.h>
#include <Crypt/RSA.h>

Skyrim::Logic::World::pointer world;

void __declspec(dllexport) Host(uint16_t pPort)
{
	world = boost::make_shared<Skyrim::Logic::World>(pPort);
}

void __declspec(dllexport) Run()
{
	try
	{
		if(world)
			world->Run();
	}
	catch(std::exception& e)
	{
		Framework::System::Log::Error(e.what());
	}
}

void __declspec(dllexport) Drop()
{
	world.reset();
}

