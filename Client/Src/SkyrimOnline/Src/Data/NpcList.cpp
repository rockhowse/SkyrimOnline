#include "stdafx.h"
#include <Data/NpcList.h>

namespace Skyrim
{
	namespace Data
	{
		NpcList::Iterator NpcList::begin()
		{
			return NpcList::Iterator(0);
		}

		NpcList::Iterator NpcList::end()
		{
			return NpcList::Iterator(NpcList::size());
		}

		uint32_t NpcList::size()
		{
			return SkyrimScript::NpcListCount();
		}

		NpcList::Iterator::Iterator(int pPos)
			:mPos(pPos)
		{
		}

		NpcList::Iterator::Iterator(const Iterator& pItor)
			:mPos(pItor.mPos)
		{
		}

		NpcList::Iterator& NpcList::Iterator::operator++()
		{
			++mPos;
			return *this;
		}

		NpcList::Iterator& NpcList::Iterator::operator++(int)
		{
			NpcList::Iterator it(*this);
			operator++();
			return it;
		}

		bool NpcList::Iterator::operator==(const Iterator& pItor)
		{
			return pItor.mPos == mPos;
		}

		bool NpcList::Iterator::operator!=(const Iterator& pItor)
		{
			return pItor.mPos != mPos;
		}

		FreeScript::TESNPC* NpcList::Iterator::operator*()
		{
			return SkyrimScript::NpcListAt(mPos);
		}

	}
}