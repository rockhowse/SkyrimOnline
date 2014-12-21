#include <Engine\SkyrimOnline.h>

namespace GameModule
{
	namespace Engine
	{
		SkyrimOnline::SkyrimOnline()
		{
			auto SkyrimOnlineDll = GetModuleHandleA("SkyrimOnline.dll");

			if (!SkyrimOnlineDll)
				SkyrimOnlineDll = LoadLibraryA("SkyrimOnline.dll");

			setPlayerControls = (tSetPlayerControls)GetProcAddress(SkyrimOnlineDll, "SetPlayerControls");
			setInChargen = (tsetInChargen)GetProcAddress(SkyrimOnlineDll, "SetInChargen");
		}

		void SkyrimOnline::SetPlayerControls(bool Enable)
		{
			setPlayerControls(Enable);
		}

		void SkyrimOnline::SetInChargen(bool abDisableSaving, bool abDisableWaiting, bool abShowControlsDisabledMessage)
		{
			setInChargen(abDisableSaving, abDisableWaiting, abShowControlsDisabledMessage);
		}
	}
}