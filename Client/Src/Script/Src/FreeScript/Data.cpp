#include "stdafx.h"
#include "Data.hpp"

namespace FreeScript
{
	DataHolder* DataHolder::GetInstance()
	{
		return *((DataHolder**)0x012E1EB8);
	}
}