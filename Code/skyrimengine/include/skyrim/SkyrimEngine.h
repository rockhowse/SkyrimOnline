#include "SkyrimPrefix.h"
#include <skyscript.h>

namespace Skyrim
{
	void SKYRIM_API SetPlayerControls(bool Enable);
	void SKYRIM_API SetInChargen(bool abDisableSaving, bool abDisableWaiting, bool abShowControlsDisabledMessage);
	void SKYRIM_API Notification(const std::string& acText);
}