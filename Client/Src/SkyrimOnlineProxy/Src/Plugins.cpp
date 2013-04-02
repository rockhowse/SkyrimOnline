#include "stdafx.h"
#include "Plugins.hpp"

using namespace boost::filesystem;

typedef LONG (__thiscall *tVMUpdate)(void* pthis, float a2);
tVMUpdate oVMUpdate;

uint32_t elapsed = 0;

LONG __fastcall VMUpdate(void* pthis, void* fastcall, float a2)
{

	if(FreeScript::Game::GetPlayer() && FreeScript::Game::GetPlayer()->parentCell)
	{
		if(elapsed == 0)
		{
			elapsed = clock();
		}
		if(clock() - elapsed > 2000)
			PluginManager::GetInstance()->Run();
	}
	else
	{
		elapsed = 0;
	}
	
	return oVMUpdate(pthis, a2);
}

void InstallPapyrusHook()
{
	PluginManager::Create();
	PluginManager::GetInstance()->Load();
	oVMUpdate = (tVMUpdate)DetourFunction((PBYTE)0xc52840, (PBYTE)VMUpdate);
}

void UninstallPapyrusHook()
{
	PluginManager::Delete();
}

typedef IRunnable* (*InitFunc)();

Plugin::Plugin(const std::string& pName)
	:runnable(nullptr)
{
	module = LoadLibraryA(pName.c_str());
	if(module)
	{
		InitFunc func = (InitFunc)GetProcAddress(module, "Initialize");
		if(func)
		{
			runnable = func();
		}
	}
}

Plugin::~Plugin()
{
	delete runnable;
	FreeLibrary(module);
}

IRunnable* Plugin::GetRunnable()
{
	return runnable;
}

PluginManager* PluginManager::instance = nullptr;

void PluginManager::Load()
{	
	boost::filesystem::path slash("/");
	std::wstring preferredSlash = slash.make_preferred().native();

	path p(std::wstring(L".") + preferredSlash + std::wstring(L"Modules"));
	if(exists(p))
	{
		std::vector<path> paths;
		std::copy(directory_iterator(p), directory_iterator(), std::back_inserter(paths));
		std::sort(paths.begin(), paths.end());

		for (auto it = paths.begin(); it != paths.end(); ++it)
		{
			if(!is_directory(*it) && it->has_extension() && it->extension().string() == std::string(".dll"))
			{
				plugins.push_back(std::make_shared<Plugin>(it->string()));
			}
		}
	}

}

void PluginManager::Run()
{
	for(auto p : plugins)
	{
		auto runnable = p->GetRunnable();
		if(runnable)
			runnable->Update();
	}
}