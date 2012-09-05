#pragma once

namespace FreeScript
{
	class BSExtraData
	{
	public:
		BSExtraData();
		virtual ~BSExtraData();

		BSExtraData* next;
	};

	class BaseExtraList
	{
	public:
		BaseExtraList();
		~BaseExtraList();

		struct PresenceBitfield
		{
			bool HasType(uint32_t type) const
			{
				uint32_t index = (type >> 3);
				uint32_t bitMask = 1 << (type % 8);
				return (bits[index] & bitMask) != 0;
			}

			uint8_t	bits[0x18];
		};

		bool HasType(uint32_t type) const 
		{
			if (mPresence) 
				return mPresence->HasType(type);
			return false;
		}

		void MarkType(uint32_t type, bool pCleared)
		{
			uint32_t index = (type >> 3);
			uint8_t bitMask = 1 << (type % 8);
			uint8_t& flag = mPresence->bits[index];
			if (pCleared) {
				flag &= ~bitMask;
			} else {
				flag |= bitMask;
			}
		}

		bool Remove(uint8_t pType, BSExtraData* pToRemove);
		bool Add(uint8_t pType, BSExtraData* pToAdd);

		BSExtraData* GetByType(uint32_t pType) const;
		BSExtraData* mData;	
		PresenceBitfield* mPresence;
	};
}