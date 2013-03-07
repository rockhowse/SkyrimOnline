#pragma once

void InstallPapyrusHook();

class IRunnable
{
public:
	virtual ~IRunnable() = 0;
	virtual void Update() = 0;
};

class Plugin
{
public:

	Plugin(const std::string& pName);
	~Plugin();

	IRunnable* GetRunnable();

private:

	IRunnable* runnable;
	HMODULE module;
};

class PluginManager
{
public:

	void Load();
	void Run();

	static PluginManager* GetInstance()
	{
		return &instance;
	}

private:

	std::vector<std::shared_ptr<Plugin>> plugins;
	static PluginManager instance;
};
