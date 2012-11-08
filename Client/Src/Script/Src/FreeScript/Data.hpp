#pragma once

#include "Types.hpp"

namespace FreeScript
{
	class TESNPC;
	class TESDataHandler
	{
	public:

		static TESDataHandler* GetInstance();

		char pad00to20c[0x20c];
		Vector<TESNPC*>	mNpcs;
	};
}