#include "Game.h"

#pragma managed

namespace Skyrim
{
	void Skyrim::SetPlayerControls(bool Enable)
	{
		if (Enable == true)
			Game::EnablePlayerControls(true, true, true, true, true, true, true, true, 0);
		else
			Game::DisablePlayerControls(true, true, true, true, true, true, true, true, 0);
	}

	void Skyrim::SetInChargen(bool abDisableSaving, bool abDisableWaiting, bool abShowControlsDisabledMessage)
	{
		Game::SetInChargen(abDisableSaving, abDisableWaiting, abShowControlsDisabledMessage);
	}
}