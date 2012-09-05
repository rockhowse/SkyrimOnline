#include "stdafx.h"
#include "Location.h"
#include "../FreeScript/Forms.hpp"

namespace SkyrimScript
{
	// Use BGSLocation*
	const char* GetLocationString(void* pLocation)
	{
		auto location = (FreeScript::BGSLocation*)pLocation;
		if(location && location->fullName.name.data)
			return location->fullName.name.data;
		return "";
	}

	// Use BGSLocation*
	uint32_t GetLocationId(void* pLocation)
	{
		auto location = (FreeScript::BGSLocation*)pLocation;
		return location->formID;
	}
}