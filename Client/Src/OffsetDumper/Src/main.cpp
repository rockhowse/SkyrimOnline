#include "stdafx.h"
#include "Plugin.hpp"

extern "C"
{
	__declspec(dllexport) IRunnable* Initialize()
	{
		return new TestPlugin;
	}
};
