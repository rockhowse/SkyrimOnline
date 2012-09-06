#pragma once

#include "Types.hpp"

namespace FreeScript
{
	class TESNPC;
	class DataHolder
	{
	public:

		static DataHolder* GetInstance();

		char pad00to20c[0x20c];
		Vector<TESNPC*>	mNpcs;
	};
}