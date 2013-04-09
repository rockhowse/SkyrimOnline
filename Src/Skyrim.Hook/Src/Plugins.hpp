#pragma once

#include <vector>
#include <xmemory>
#include <windows.h>
#include <memory>

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