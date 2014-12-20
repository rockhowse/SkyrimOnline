#pragma once

#include <stdafx.h>

#include <Overlay\GUI.h>
#include <Overlay\Chat.h>

namespace GameModule
{
	namespace Engine
	{
		class SkyrimOnline
		{
			public:
			
			SkyrimOnline();

			void SetPlayerControls(bool Enable);
			void SetInChargen(bool abDisableSaving, bool abDisableWaiting, bool abShowControlsDisabledMessage);

			private:

			typedef void(*tSetPlayerControls)(bool Enable);
			tSetPlayerControls setPlayerControls;

			typedef void(*tsetInChargen)(bool abDisableSaving, bool abDisableWaiting, bool abShowControlsDisabledMessage);
			tsetInChargen setInChargen;
			
		};
	}
}