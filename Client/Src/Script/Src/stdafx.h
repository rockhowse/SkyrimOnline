#pragma once

#define DIRECTINPUT_VERSION 0x0800

#include <common/IPrefix.h>

#include <list>
#include <vector>
#include <ctime>
#include <fstream>
#include <deque>
#include <concurrent_queue.h>
#include <unordered_map>
#include <cstdint>
#include <array>

#include <common/skyscript.h>
#include <common/obscript.h>
#include <common/types.h>
#include <common/enums.h>
#include <common/plugin.h>
#include <common/Utils.h>


#include <skse/skse_version.h>
#include <skse/SafeWrite.h>
#include <skse/GameAPI.h>
#include <skse/GameData.h>
#include <skse/GameReferences.h>
#include <skse/GameFormComponents.h>
#include <skse/GameRTTI.h>
#include <skse/GameForms.h>
#include <skse/GameObjects.h>
#include <skse/PapyrusActorBase.h>

#pragma warning( disable : 4251 )
#pragma warning( disable : 4244 )
#pragma warning( disable : 4996 )
#pragma warning( disable : 4355 )