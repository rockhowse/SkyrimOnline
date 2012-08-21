#include "stdafx.h"
#include <Data/ActorList.h>

namespace Skyrim
{
	namespace Data
	{
		ActorList::Iterator ActorList::begin()
		{
			return ActorList::Iterator(0);
		}

		ActorList::Iterator ActorList::end()
		{
			return ActorList::Iterator(ActorList::size());
		}

		uint32_t ActorList::size()
		{
			return SkyrimScript::ActorListCount();
		}

		ActorList::Iterator::Iterator(int pPos)
			:mPos(pPos)
		{
		}

		ActorList::Iterator::Iterator(const Iterator& pItor)
			:mPos(pItor.mPos)
		{
		}

		ActorList::Iterator& ActorList::Iterator::operator++()
		{
			++mPos;
			return *this;
		}

		ActorList::Iterator& ActorList::Iterator::operator++(int)
		{
			ActorList::Iterator it(*this);
			operator++();
			return it;
		}

		bool ActorList::Iterator::operator==(const Iterator& pItor)
		{
			return pItor.mPos == mPos;
		}

		bool ActorList::Iterator::operator!=(const Iterator& pItor)
		{
			return pItor.mPos != mPos;
		}

		CActor* ActorList::Iterator::operator*()
		{
			return (CActor*)SkyrimScript::ActorListAt(mPos);
		}

	}
}