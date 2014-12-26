#pragma once

#include <Engine/Controllers/SkyrimHelpers.h>
#include <skyscript.h>
#include <GameForms.h>
#include <GameReferences.h>
#include <GameObjects.h>
#include <GameFormComponents.h>
#include <GameRTTI.h>

namespace Logic
{
	namespace Engine
	{
		namespace Controllers
		{
			void Serialize(TESBoundObject::Bound* apBound, Messages::Vector3& aBound)
			{
				aBound.x = apBound->x;
				aBound.y = apBound->y;
				aBound.z = apBound->z;
			}

			void Deserialize(TESBoundObject::Bound* apBound, const Messages::Vector3& aBound)
			{
				apBound->x = aBound.x;
				apBound->y = aBound.y;
				apBound->z = aBound.z;
			}

			void Serialize(TESActorBaseData* apActorBaseData, Messages::ActorBaseData& aActorBaseData)
			{
				aActorBaseData.flags = apActorBaseData->flags;
				aActorBaseData.unk08 = apActorBaseData->unk08;
				aActorBaseData.unk0A = apActorBaseData->unk0A;
				aActorBaseData.level = apActorBaseData->level;
				aActorBaseData.minLevel = apActorBaseData->minLevel;
				aActorBaseData.maxLevel = apActorBaseData->maxLevel;
				aActorBaseData.unk12 = apActorBaseData->unk12;
				aActorBaseData.unk14 = apActorBaseData->unk14;
				aActorBaseData.unk16 = apActorBaseData->unk16;
				aActorBaseData.unk18 = apActorBaseData->unk18;
				aActorBaseData.unk1A = apActorBaseData->unk1A;
				aActorBaseData.unk1C = apActorBaseData->unk1C;
				aActorBaseData.voiceId = apActorBaseData->voiceType->formID;
				aActorBaseData.unk24 = apActorBaseData->unk24;
				aActorBaseData.unk28 = apActorBaseData->unk28;

				aActorBaseData.factions.clear();
				for (UInt32 i = 0; i < apActorBaseData->factions.count; ++i)
				{
					Messages::FactionInfo info;
					if (apActorBaseData->factions[i].faction)
					{
						info.factionId = apActorBaseData->factions[i].faction->formID;
					}
					else
					{
						info.factionId = 0;
					}
					info.rank = apActorBaseData->factions[i].rank;

					aActorBaseData.factions.push_back(info);
				}
			}

			void Deserialize(TESActorBaseData* apActorBaseData, const Messages::ActorBaseData& aActorBaseData)
			{
				apActorBaseData->flags = aActorBaseData.flags;
				apActorBaseData->unk08 = aActorBaseData.unk08;
				apActorBaseData->unk0A = aActorBaseData.unk0A;
				apActorBaseData->level = aActorBaseData.level;
				apActorBaseData->minLevel = aActorBaseData.minLevel;
				apActorBaseData->maxLevel = aActorBaseData.maxLevel;
				apActorBaseData->unk12 = aActorBaseData.unk12;
				apActorBaseData->unk14 = aActorBaseData.unk14;
				apActorBaseData->unk16 = aActorBaseData.unk16;
				apActorBaseData->unk18 = aActorBaseData.unk18;
				apActorBaseData->unk1A = aActorBaseData.unk1A;
				apActorBaseData->unk1C = aActorBaseData.unk1C;
				apActorBaseData->voiceType = (BGSVoiceType*)LookupFormByID(aActorBaseData.voiceId);
				apActorBaseData->unk24 = aActorBaseData.unk24;
				apActorBaseData->unk28 = aActorBaseData.unk28;

				apActorBaseData->factions.Allocate(aActorBaseData.factions.size());

				for (UInt32 i = 0; i < aActorBaseData.factions.size(); ++i)
				{
					if (aActorBaseData.factions[i].factionId)
					{
						apActorBaseData->factions[i].faction = (TESFaction *)LookupFormByID(aActorBaseData.factions[i].factionId);
					}
					else
					{
						apActorBaseData->factions[i].faction = nullptr;
					}
					apActorBaseData->factions[i].rank = aActorBaseData.factions[i].rank;
				}
			}

			void Serialize(TESContainer* apContainer, Messages::TESContainer& aContainer)
			{
				aContainer.entries.resize(apContainer->numEntries);
				for (UInt32 i = 0; i < apContainer->numEntries; ++i)
				{
					aContainer.entries[i].count = apContainer->entries[i]->count;
					if (apContainer->entries[i]->form->formID)
					{
						aContainer.entries[i].formId = apContainer->entries[i]->form->formID;
					}
					else
					{
						aContainer.entries[i].formId = 0;
					}

					if (apContainer->entries[i]->data)
					{
						aContainer.entries[i].unk00 = apContainer->entries[i]->data->unk00;
						aContainer.entries[i].unk04 = apContainer->entries[i]->data->unk04;
						aContainer.entries[i].unk08 = apContainer->entries[i]->data->unk08;
					}
					else
					{
						aContainer.entries[i].unk00 = 0;
						aContainer.entries[i].unk04 = 0;
						aContainer.entries[i].unk08 = 0;
					}
				}
			}

			void Deserialize(TESContainer* apContainer, const Messages::TESContainer& aContainer)
			{
				apContainer->numEntries = aContainer.entries.size();
				apContainer->entries = (TESContainer::Entry**)FormHeap_Allocate(sizeof(TESContainer::Entry*) * apContainer->numEntries);
				for (UInt32 i = 0; i < apContainer->numEntries; ++i)
				{
					apContainer->entries[i] = (TESContainer::Entry*)FormHeap_Allocate(sizeof(TESContainer::Entry));
					apContainer->entries[i]->count = aContainer.entries[i].count;
					if (aContainer.entries[i].formId)
					{
						apContainer->entries[i]->form = (TESForm*)ScriptDragon::Game::GetFormById(aContainer.entries[i].formId);
					}
					else
					{
						apContainer->entries[i]->form = nullptr;
					}

					apContainer->entries[i]->data = (TESContainer::Entry::Data*)FormHeap_Allocate(sizeof(TESContainer::Entry::Data));
					apContainer->entries[i]->data->unk00 = aContainer.entries[i].unk00;
					apContainer->entries[i]->data->unk04 = aContainer.entries[i].unk04;
					apContainer->entries[i]->data->unk08 = aContainer.entries[i].unk08;

				}
			}

			void Serialize(TESSpellList* apTES, Messages::TESpellList& aMessage)
			{
				if (apTES->unk04)
				{
					aMessage.spellIds.resize(apTES->unk04->numSpells);
					aMessage.formIds.resize(apTES->unk04->numUnk4);
					aMessage.shoutIds.resize(apTES->unk04->numShouts);

					for (UInt32 i = 0; i < apTES->unk04->numSpells; ++i)
					{
						aMessage.spellIds[i] = apTES->unk04->spells[i]->formID;
					}
					for (UInt32 i = 0; i < apTES->unk04->numUnk4; ++i)
					{
						aMessage.formIds[i] = apTES->unk04->unk4[i]->formID;
					}
					for (UInt32 i = 0; i < apTES->unk04->numShouts; ++i)
					{
						aMessage.shoutIds[i] = apTES->unk04->shouts[i]->formID;
					}
				}
			}

			void Deserialize(TESSpellList* apTES, const Messages::TESpellList& aMessage)
			{
				if (!apTES->unk04)
				{
					apTES->unk04 = (TESSpellList::Data*)FormHeap_Allocate(sizeof(TESSpellList::Data));
				}

				apTES->unk04->numSpells = aMessage.spellIds.size();
				apTES->unk04->numUnk4 = aMessage.formIds.size();
				apTES->unk04->numShouts = aMessage.shoutIds.size();

				apTES->unk04->spells = (SpellItem**)FormHeap_Allocate(sizeof(SpellItem*) * apTES->unk04->numSpells);
				apTES->unk04->unk4 = (TESForm**)FormHeap_Allocate(sizeof(TESForm*) * apTES->unk04->numUnk4);
				apTES->unk04->shouts = (TESShout**)FormHeap_Allocate(sizeof(TESShout*) * apTES->unk04->numShouts);

				for (UInt32 i = 0; i < apTES->unk04->numSpells; ++i)
				{
					apTES->unk04->spells[i] = (SpellItem*)LookupFormByID(aMessage.spellIds[i]);
				}
				for (UInt32 i = 0; i < apTES->unk04->numUnk4; ++i)
				{
					apTES->unk04->unk4[i] = (TESForm*)LookupFormByID(aMessage.formIds[i]);
				}
				for (UInt32 i = 0; i < apTES->unk04->numShouts; ++i)
				{
					apTES->unk04->shouts[i] = (TESShout*)LookupFormByID(aMessage.shoutIds[i]);
				}
			}

			void Serialize(TESNPC::FaceMorphs* apTES, Messages::FaceMorphs& aMessage)
			{
				aMessage.options.resize(TESNPC::FaceMorphs::kNumOptions);
				for (UInt32 i = 0; i < TESNPC::FaceMorphs::kNumOptions; ++i)
				{
					aMessage.options[i] = apTES->option[i];
				}

				aMessage.preset0 = apTES->presets[0];
				aMessage.preset1 = apTES->presets[1];
				aMessage.preset2 = apTES->presets[2];
				aMessage.preset3 = apTES->presets[3];
			}

			void Deserialize(TESNPC::FaceMorphs* apTES, const Messages::FaceMorphs& aMessage)
			{
				for (UInt32 i = 0; i < TESNPC::FaceMorphs::kNumOptions; ++i)
				{
					apTES->option[i] = aMessage.options[i];
				}

				apTES->presets[0] = aMessage.preset0;
				apTES->presets[1] = aMessage.preset1;
				apTES->presets[2] = aMessage.preset2;
				apTES->presets[3] = aMessage.preset3;
			}

			void Serialize(TESNPC* apNpc, Messages::Npc& aNpc)
			{
				aNpc.flags = apNpc->flags;
				aNpc.unk10 = apNpc->unk10;
				aNpc.formType = apNpc->formType;

				// Bounds
				Serialize(&apNpc->bounds, aNpc.bound1);
				Serialize(&apNpc->bounds2, aNpc.bound2);

				// ActorBase
				Serialize(&apNpc->actorData, aNpc.actorBaseData);
				Serialize(&apNpc->container, aNpc.container);
				Serialize(&apNpc->spellList, aNpc.spellList);

				aNpc.skinId = 0;
				if (apNpc->skinForm.skin)
				{
					aNpc.skinId = apNpc->skinForm.skin->formID;
				}
				
				aNpc.keywordIds.resize(apNpc->keyword.numKeywords);
				for (UInt32 i = 0; i < apNpc->keyword.numKeywords; ++i)
				{
					aNpc.keywordIds[i] = apNpc->keyword.keywords[i]->formID;
				}

				// TODO add perk ranks

				aNpc.raceId = apNpc->race.race->formID;

				aNpc.overridePacks.unk04 = apNpc->overridePacks.unk04;
				aNpc.overridePacks.unk08 = apNpc->overridePacks.unk08;
				aNpc.overridePacks.unk0C = apNpc->overridePacks.unk0C;
				aNpc.overridePacks.unk10 = apNpc->overridePacks.unk10;

				aNpc.unk10A = apNpc->unk10A;
				aNpc.classId = apNpc->npcClass->formID;

				aNpc.hairColor.fullName.data = apNpc->headData->hairColor->fullName.name.data;
				aNpc.hairColor.abgr = apNpc->headData->hairColor->abgr;
				aNpc.hairColor.unk20 = apNpc->headData->hairColor->unk20;

				aNpc.headTextureId = apNpc->headData->headTexture->formID;
				
				aNpc.unk114 = apNpc->unk114;
				aNpc.combatStyleId = apNpc->combatStyle->formID;
				aNpc.unk11C = apNpc->unk11C;
				aNpc.overlayId = 0;
				if (apNpc->overlayRace)
				{
					aNpc.overlayId = apNpc->overlayRace->formID;
				}

				aNpc.height = apNpc->height;
				aNpc.weight = apNpc->weight;

				aNpc.outfitId = 0;
				aNpc.skinFarId = 0;
				aNpc.sleepOutfitId = 0;

				if (apNpc->skinFar)
				{
					aNpc.skinFarId = apNpc->skinFar->formID;
				}
				if (apNpc->defaultOutfit)
				{
					aNpc.outfitId = apNpc->defaultOutfit->formID;
				}
				if (apNpc->sleepOutfit)
				{
					aNpc.sleepOutfitId = apNpc->sleepOutfit->formID;
				}
				
				aNpc.unk144 = apNpc->unk144;

				aNpc.factionId = 0;
				if (apNpc->faction)
				{
					aNpc.factionId = apNpc->faction->formID;
				}

				aNpc.headpartIds.resize(apNpc->numHeadParts);
				for (UInt32 i = 0; i < apNpc->numHeadParts; ++i)
				{
					aNpc.headpartIds[i] = apNpc->headparts[i]->formID;
				}

				aNpc.unk151 = apNpc->unk151;
				aNpc.unk152 = apNpc->unk152;
				aNpc.unk153 = apNpc->unk153;

				aNpc.red = apNpc->color.red;
				aNpc.green = apNpc->color.green;
				aNpc.blue = apNpc->color.blue;

				aNpc.unk158 = apNpc->unk158;

				Serialize(apNpc->faceMorph, aNpc.faceMorphs);

				aNpc.unk160 = apNpc->unk160;
			}

			void Deserialize(TESNPC* apNpc, const Messages::Npc& aNpc)
			{
				apNpc->flags = aNpc.flags;
				apNpc->unk10 = aNpc.unk10;
				apNpc->formType = aNpc.formType;

				// Bounds
				Deserialize(&apNpc->bounds, aNpc.bound1);
				Deserialize(&apNpc->bounds2, aNpc.bound2);

				// ActorBase
				Deserialize(&apNpc->actorData, aNpc.actorBaseData);
				Deserialize(&apNpc->container, aNpc.container);
				Deserialize(&apNpc->spellList, aNpc.spellList);
				
				if (aNpc.skinId)
				{

					apNpc->skinForm.skin = (TESObjectARMO *)LookupFormByID(aNpc.skinId);
				}
				else
				{
					apNpc->skinForm.skin = nullptr;
				}

				apNpc->keyword.numKeywords = aNpc.keywordIds.size();
				apNpc->keyword.keywords = (BGSKeyword**)FormHeap_Allocate(sizeof(void*) * apNpc->keyword.numKeywords);
				for (UInt32 i = 0; i < apNpc->keyword.numKeywords; ++i)
				{
					apNpc->keyword.keywords[i] = (BGSKeyword *)LookupFormByID(aNpc.keywordIds[i]);
				}

				// TODO add perk rank

				apNpc->race.race = (TESRace *)LookupFormByID(aNpc.raceId);

				apNpc->overridePacks.unk04 = aNpc.overridePacks.unk04;
				apNpc->overridePacks.unk08 = aNpc.overridePacks.unk08;
				apNpc->overridePacks.unk0C = aNpc.overridePacks.unk0C;
				apNpc->overridePacks.unk10 = aNpc.overridePacks.unk10;

				apNpc->unk10A = aNpc.unk10A;
				apNpc->npcClass = (TESClass*)LookupFormByID(aNpc.classId);

				if (apNpc->headData == nullptr)
				{
					apNpc->headData = (TESNPC::HeadData*)FormHeap_Allocate(sizeof(TESNPC::HeadData));
				}

				apNpc->headData->hairColor = (BGSColorForm*)IFormFactory::GetFactoryForType(kFormType_ColorForm)->Create();
				apNpc->headData->hairColor->unk20 = aNpc.hairColor.unk20;
				apNpc->headData->hairColor->abgr = aNpc.hairColor.abgr;

				apNpc->headData->headTexture = (BGSTextureSet *)LookupFormByID(aNpc.headTextureId);

				apNpc->unk114 = aNpc.unk114;
				apNpc->combatStyle = (TESCombatStyle*)LookupFormByID(aNpc.combatStyleId);
				apNpc->unk11C = aNpc.unk11C;
				if (aNpc.overlayId)
					apNpc->overlayRace = (TESRace *)LookupFormByID(aNpc.overlayId);
				apNpc->height = aNpc.height;
				apNpc->weight = aNpc.weight;
				if (aNpc.skinFarId)
					apNpc->skinFar = (TESObjectARMO*)LookupFormByID(aNpc.skinFarId);
				if (aNpc.outfitId)
					apNpc->defaultOutfit = (BGSOutfit*)LookupFormByID(aNpc.outfitId);
				if (aNpc.sleepOutfitId)
					apNpc->sleepOutfit = (BGSOutfit*)LookupFormByID(aNpc.sleepOutfitId);
				apNpc->unk144 = aNpc.unk144;
				if (aNpc.factionId)
					apNpc->faction = (TESFaction*)LookupFormByID(aNpc.factionId);

				apNpc->numHeadParts = aNpc.headpartIds.size();
				if (apNpc->headparts)
				{
					FormHeap_Free(apNpc->headparts);
				}

				apNpc->headparts = (BGSHeadPart**)FormHeap_Allocate(sizeof(void*) * apNpc->numHeadParts);

				for (UInt32 i = 0; i < apNpc->numHeadParts; ++i)
				{
					apNpc->headparts[i] = (BGSHeadPart *)LookupFormByID(aNpc.headpartIds[i]);
				}

				apNpc->unk151 = aNpc.unk151;
				apNpc->unk152 = aNpc.unk152;
				apNpc->unk153 = aNpc.unk153;

				apNpc->color.red = aNpc.red;
				apNpc->color.green = aNpc.green;
				apNpc->color.blue = aNpc.blue;

				apNpc->unk158 = aNpc.unk158;

				Deserialize(apNpc->faceMorph, aNpc.faceMorphs);

				apNpc->unk160 = aNpc.unk160;
			}
		}
	}
}