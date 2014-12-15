#pragma once

#include "Common.h"
#include "References.h"
#include "RTTI.h"

namespace Skyrim
{
	class ActorHelper : public BaseHelper<Skyrim::Actor>
	{
	public:
		ActorHelper(Skyrim::Actor* ptr) : BaseHelper<Skyrim::Actor>(ptr){};

		TESNPC* GetNpc()
		{
			return rtti_cast(mData->baseForm, TESForm, TESNPC);
		}
	};
}