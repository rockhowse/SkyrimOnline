#include "Actor.h"
#include "References.h"
#include "RTTI.h"
#include "skyscript.h"

namespace Skyrim
{
	void QueueNiNodeUpdate(Skyrim::Actor* ptr)
	{
		((void(__thiscall*)(Skyrim::Actor*,bool))0x730ee0)(ptr,true);
	}

	void SetName(Skyrim::Actor* pActor, const std::string& pName)
	{
		if(!pActor) return;
		Skyrim::TESNPC* npc = rtti_cast(pActor->baseForm, TESForm, TESNPC);
		if(!npc) return;
		npc->fullName.name = Skyrim::BSFixedString(pName.c_str());
	}

	Skyrim::TESForm* GetWornForm(Skyrim::Actor* ptr, uint32_t mask)
	{
		if(!ptr)
			return nullptr;

		Skyrim::ExtraContainerChanges* pContainerChanges = ptr->extraData.GetExtraContainerChanges();
		if (pContainerChanges) 
		{
			for(auto node = pContainerChanges->data->objList->Head(); node ; node = node->next)
			{
				if(node->item)
				{
					auto extendList = node->item->extendDataList;

					auto matcher = [mask](Skyrim::TESForm* pForm) -> bool 
					{
						if (pForm) 
						{
							Skyrim::BGSBipedObjectForm* pBip = rtti_cast(pForm, TESForm, BGSBipedObjectForm);
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

	::Skyrim::Actor* GetPlayer()
	{
		return (::Skyrim::Actor*)::Game::GetPlayer();
	}
}