#include "stdafx.h"
#include "Plugins.hpp"
#include <FreeScript/Memory.hpp>

using namespace boost::filesystem;

typedef LONG (__thiscall *tVMUpdate)(void* pthis, float a2);
typedef void (__thiscall *dtor)(void* pthis);
typedef int (__cdecl *tGetForm)(int,int,int,int);
typedef char (__thiscall *tsub_C55DA0)(int , int, int , int , void **);
tVMUpdate oVMUpdate;
tGetForm oGetForm;
tsub_C55DA0 osub;

uint32_t elapsed = 0;

char __fastcall sub_C55DA0(int _this, void* fastcall, int d0, int hash, int cname, void **a5)
{
	//file << hash << " cname : " << (char*)cname << std::endl;
	return osub(_this, d0, hash, cname, a5);
}

void test()
{
	SkyrimVM::GetInstance()->registry->registrationMap;
}

LONG __fastcall VMUpdate(void* pthis, void* fastcall, float a2)
{
	LONG ret = oVMUpdate(pthis, a2);

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
	
	return ret;
}

int __cdecl h_GetForm(int a1, int a2, int a3, int a4)
{
	file << std::hex << a1 << " " << a2 << " " << a3 << std::endl;
	return oGetForm(a1, a2, a3, a4);
}

void InstallPapyrusHook()
{
	void** vtbl = *(void***)SkyrimVM::GetInstance()->registry;
	if(!PluginManager::GetInstance())
	{
		file << std::hex << *(vtbl + 16);
		PluginManager::Create();
		PluginManager::GetInstance()->Load();
		oVMUpdate = (tVMUpdate)DetourFunction((PBYTE)/*0xc52840*/0x8D40D0, (PBYTE)VMUpdate);
		oGetForm = (tGetForm)DetourFunction((PBYTE)0x8f0c10, (PBYTE)h_GetForm);
		osub = (tsub_C55DA0)DetourFunction((PBYTE)0xC55DA0, (PBYTE)sub_C55DA0);
	}
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