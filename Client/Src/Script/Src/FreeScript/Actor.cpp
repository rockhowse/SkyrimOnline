#include "stdafx.h"
#include "Actor.hpp"
#include "References.hpp"
#include "RTTI.hpp"

namespace FreeScript
{
	void QueueNiNodeUpdate(FreeScript::Actor* ptr)
	{
		((void(__thiscall*)(FreeScript::Actor*,bool))0x007309B0)(ptr,true);
	}

	void SetName(FreeScript::Actor* pActor, const std::string& pName)
	{
		if(!pActor) return;
		FreeScript::TESNPC* npc = rtti_cast(pActor->baseForm, TESForm, TESNPC);
		if(!npc) return;
		npc->fullName.name = FreeScript::String(pName.c_str());
	}

	FreeScript::TESForm* GetWornForm(FreeScript::Actor* ptr, uint32_t mask)
	{
		if(!ptr)
			return nullptr;

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