#include <stdafx.h>
#include <skyscript.h>

namespace Skyrim
{
	extern "C" __declspec(dllexport) void SetPlayerControls(bool Enable);
	extern "C" __declspec(dllexport) void SetInChargen(bool abDisableSaving, bool abDisableWaiting, bool abShowControlsDisabledMessage);
}