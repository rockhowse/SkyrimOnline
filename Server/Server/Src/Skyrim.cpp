#define _CRT_SECURE_NO_WARNINGS

#include <Logic/World.h>
#include <System/Log.h>
#include <Crypt/RSA.h>

__declspec(dllexport) void* Host(uint16_t pPort)
{
	return (void*)new Skyrim::Logic::World(pPort);
}

__declspec(dllexport) void Run(void* ptr)
{
	try
	{
		Skyrim::Logic::World* world = (Skyrim::Logic::World*)ptr;
		if(world)
			world->Run();
	}
	catch(std::exception& e)
	{
		Framework::System::Log::Error(e.what());
	}
}

__declspec(dllexport) void Drop(void* ptr)
{
	Skyrim::Logic::World* world = (Skyrim::Logic::World*)ptr;
	delete world; 
}

