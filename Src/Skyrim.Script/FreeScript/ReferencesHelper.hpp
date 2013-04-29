#pragma once

#include "Common.hpp"
#include "References.hpp"
#include "RTTI.hpp"

namespace FreeScript
{
	class ActorHelper : public BaseHelper<FreeScript::Actor>
	{
	public:
		ActorHelper(FreeScript::Actor* ptr) : BaseHelper<FreeScript::Actor>(ptr){};

		TESNPC* GetNpc()
		{
			return rtti_cast(mData->baseForm, TESForm, TESNPC);
		}
	};
}