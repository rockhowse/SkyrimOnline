#pragma once

class IRunnable
{
public:
	virtual ~IRunnable(){};
	virtual void Update() = 0;
};

class TestPlugin : public IRunnable
{
public:

	TestPlugin();
	~TestPlugin();
	void Update();

private:

	bool ran;
	clock_t time;
};