#include "stdafx.h"
#include "Actor.hpp"
#include "References.hpp"
#include "RTTI.hpp"

namespace FreeScript
{
	void QueueNiNode(void* ptr)
	{
		((void(__thiscall*)(CActor*))0x0072CD80)((CActor*)ptr);
	}

	::FreeScript::TESForm* GetBaseForm(void* ptr)
	{
		return (TESForm*)((char*)ptr + 0x24);
	}

	::FreeScript::TESNPC* GetNpc(::FreeScript::TESForm* ptr)
	{
		return (::FreeScript::TESNPC*)((char*)ptr + 0xC4);
	}

	uint32_t GetNpcFormID(::FreeScript::TESNPC* ptr)
	{
		return ptr->race.race->formID;
	}

	FreeScript::TESForm* GetWornForm(::FreeScript::Actor* ptr, uint32_t mask)
	{
		FreeScript::ExtraContainerChanges* pContainerChanges = ptr->extraData.GetExtraContainerChanges();
		if (pContainerChanges) 
		{
			for(auto node = pContainerChanges->data->objList->Head(); node ; node = node->next)
			{
				if(node->item)
				{
					auto extendList = node->item->extendDataList;

					auto matcher = [mask](FreeScript::TESForm* pForm) -> bool 
					{
						if (pForm) 
						{
							FreeScript::BGSBipedObjectForm* pBip = rtti_cast(pForm, TESForm, BGSBipedObjectForm);
							if (pBip) 
								return (pBip->data.parts & mask) != 0;
						}
						return false;
					};

					if (matcher(node->item->type)) 
					{ 
						unsigned i = 0;
						auto extraDataList = extendList->At(i);
						while (extraDataList) 
						{
							if (extraDataList->HasType(22) || extraDataList->HasType(23))
								return node->item->type;

							++i;
							extraDataList = extendList->At(i);
						}
					}
				}
			}
		}
		return nullptr;
	}
}