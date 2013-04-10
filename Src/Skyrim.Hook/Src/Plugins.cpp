#include "stdafx.h"
#include "Plugins.hpp"
#include <algorithm>
#include <stack>
#include "Hook/Function.hpp"
#include "common/plugin.h"

class Plugin
{
public:
	Plugin(const std::string& pName);
	~Plugin();

	void Run();

private:

	HMODULE module;
	void (__stdcall *mInitProc)();
	void (__stdcall *mUpdateProc)();
};

class PluginManager : public IPluginManager
{
public:

	void Load();
	void Run();

	static PluginManager* instance;

private:

	std::vector<std::shared_ptr<Plugin>> mPlugins;
};

PluginManager* PluginManager::instance = nullptr;

IPluginManager* GetInstance()
{
	return PluginManager::instance;
}

IPluginManager* Create()
{
	Delete();
	PluginManager::instance = new PluginManager;
	return PluginManager::instance;
}

IPluginManager* Delete()
{
	delete PluginManager::instance;
	PluginManager::instance= nullptr;
	return nullptr;
}

Plugin::Plugin(const std::string& pName)
{
	module = LoadLibraryA(pName.c_str());
	file << "Load assembly : " << pName << std::endl;
	if(module)
	{
		mInitProc = (decltype(mInitProc))GetProcAddress(module, "Initialize");
		mUpdateProc = (decltype(mUpdateProc))GetProcAddress(module, "Update");
		file << "Initialize : " << mInitProc << " | Run : " << mUpdateProc << std::endl;
		if(mInitProc && mUpdateProc)
		{
			mInitProc();
		}
	}
}

Plugin::~Plugin()
{
}

void Plugin::Run()
{
	if(mUpdateProc && mInitProc)
		mUpdateProc();
}

bool ListFiles(std::string path, std::string mask, std::vector<std::string>& files)
{
	HANDLE hFind = INVALID_HANDLE_VALUE;
	WIN32_FIND_DATA fdata;
	std::string fullpath;
	std::stack<std::string> folders;
	folders.push(path);
	files.clear();

	while (!folders.empty())
	{
		path = folders.top();
		fullpath = path + "\\" + mask;
		folders.pop();

		hFind = FindFirstFile(fullpath.c_str(), &fdata);

		if (hFind != INVALID_HANDLE_VALUE)
		{
			do
			{
				if (strcmp(fdata.cFileName, ".") != 0 &&
					strcmp(fdata.cFileName, "..") != 0)
				{
					if (fdata.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
					{
						//folders.push(path + std::string("\\") + fdata.cFileName);
					}
					else
					{
						files.push_back(path + std::string("\\") + fdata.cFileName);
					}
				}
			}
			while (FindNextFile(hFind, &fdata) != 0);
		}

		if (GetLastError() != ERROR_NO_MORE_FILES)
		{
			FindClose(hFind);

			return false;
		}

		FindClose(hFind);
		hFind = INVALID_HANDLE_VALUE;
	}

	return true;
}

void PluginManager::Load()
{	
	std::vector<std::string> files;
	ListFiles("./Modules","*.dll",files);

	for(auto f : files)
		mPlugins.push_back(std::make_shared<Plugin>(f));

}

void PluginManager::Run()
{
	for(auto p : mPlugins)
	{
		p->Run();
	}
}

#pragma managed

typedef void (__stdcall *TWait)(int);
TWait Wait;

extern "C" __declspec(dllexport) void main()
{
	auto mod = GetModuleHandle("Skyrim.Script.dll");
	Wait = (TWait)GetProcAddress(mod, "DoWait");
	while(Wait)
	{
		GetInstance()->Run();
		Wait(0);
	}
}