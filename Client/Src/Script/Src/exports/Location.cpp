#include "stdafx.h"
#include "Location.h"
#include "skse/PapyrusActor.h"
#include "skse/PapyrusActorBase.h"

namespace SkyrimScript
{
	// Use BGSLocation*
	const char* GetLocationString(void* pLocation)
	{
		BGSLocation* location = (BGSLocation*)pLocation;
		if(location && location->GetName())
			return location->GetName();
		return "";
	}

	// Use BGSLocation*
	uint32_t GetLocationId(void* pLocation)
	{
		BGSLocation* location = (BGSLocation*)pLocation;
		return location->formID;
	}
}