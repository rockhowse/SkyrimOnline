#pragma once

#include "Types.h"

namespace Skyrim
{
	class TESForm;
	class TESObjectREFR;
	class BaseExtraList;

	class BSExtraData
	{
	public:
		BSExtraData();
		virtual ~BSExtraData();

		BSExtraData* next;
	};

	class ExtraContainerChanges : public BSExtraData
	{
	public:
		ExtraContainerChanges();
		virtual ~ExtraContainerChanges();

		struct EntryData
		{
			Skyrim::TESForm* type;
			List<Skyrim::BaseExtraList>* extendDataList;
			int32_t countDelta;
		};

		struct Data
		{
			List<EntryData>*	objList;
			TESObjectREFR*	owner;
			float			totalWeight;
			float			armorWeight;
		};

		Data * data;

		struct FoundEquipData {
			TESForm* pForm;
			BaseExtraList* pExtraData;
		};
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

		Skyrim::ExtraContainerChanges* GetExtraContainerChanges() const;

		BSExtraData* mData;	
		PresenceBitfield* mPresence;
	};
}