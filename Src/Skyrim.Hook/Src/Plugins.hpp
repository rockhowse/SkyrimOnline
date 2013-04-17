#pragma once

#include <xmemory>
#include <windows.h>
#include <cstdint>

class IRunnable
{
public:
	virtual ~IRunnable() = 0;
	virtual void Update() = 0;
};


class IPluginManager
{
public:

	virtual void Load() = 0;
	virtual void Run() = 0;
};

IPluginManager* GetInstance();
IPluginManager* Create();
IPluginManager* Delete();