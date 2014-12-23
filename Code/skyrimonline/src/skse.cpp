#include "skse/PluginAPI.h"
#include "skse/skse_version.h"
#include "skse/SafeWrite.h"
#include "skse/ScaleformCallbacks.h"
#include "skse/ScaleformMovie.h"
#include "skse/GameAPI.h"
#include <DInput/Input.hpp>
#include <DirectX/DirectXHook.h>
#include "skyscript.h"
#include "WinAPI.hpp"

PluginHandle	g_pluginHandle = kPluginHandle_Invalid;
extern HMODULE g_hModule;

namespace ScriptDragon
{
	void DragonPluginInit(HMODULE hModule);
}

extern "C"
{

	bool SKSEPlugin_Query(const SKSEInterface * skse, PluginInfo * info)
	{
		_MESSAGE("Skyrim Online Query");

		// populate info structure
		info->infoVersion = PluginInfo::kInfoVersion;
		info->name = "Skyrim Online";
		info->version = 1;

		// store plugin handle so we can identify ourselves later
		g_pluginHandle = skse->GetPluginHandle();

		if (skse->isEditor)
		{
			_MESSAGE("loaded in editor, marking as incompatible");

			return false;
		}
		else if (skse->runtimeVersion != RUNTIME_VERSION_1_9_32_0)
		{
			_MESSAGE("unsupported runtime version %08X", skse->runtimeVersion);

			return false;
		}

		// supported runtime version
		return true;
	}

	bool SKSEPlugin_Load(const SKSEInterface * skse)
	{
		_MESSAGE("load");

		HookDirect3D9();
		HookDirectInput();
		HookWinAPI();

		ScriptDragon::DragonPluginInit(g_hModule);

		return true;
	}

};
