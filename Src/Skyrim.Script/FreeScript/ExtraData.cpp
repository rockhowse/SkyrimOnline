#include "stdafx.h"
#include "ExtraData.hpp"
#include "RTTI.hpp"

namespace FreeScript
{
	FreeScript::ExtraContainerChanges* BaseExtraList::GetExtraContainerChanges() const
	{
		if (!HasType(21))
			return nullptr;

		for(BSExtraData * itor = mData; itor; itor = itor->next) 
		{
			auto container = rtti_cast(itor, BSExtraData, ExtraContainerChanges);
			if (container != NULL)
				return container;
		}
		return nullptr;
	}
}