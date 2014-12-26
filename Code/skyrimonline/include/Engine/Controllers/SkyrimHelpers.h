#pragma once

#include <skse/GameReferences.h>
#include <skse/GameForms.h>
#include <skse/GameObjects.h>
#include <skse/GameFormComponents.h>
#include <messages/Client/GameCli_Handler.h>

namespace Logic
{
	namespace Engine
	{
		namespace Controllers
		{
			void Serialize(TESBoundObject::Bound* apBound, Messages::Vector3& aBound);
			void Deserialize(TESBoundObject::Bound* apBound, const Messages::Vector3& aBound);

			void Serialize(TESActorBaseData* apActorBaseData, Messages::ActorBaseData& aActorBaseData);
			void Deserialize(TESActorBaseData* apActorBaseData, const Messages::ActorBaseData& aActorBaseData);

			void Serialize(TESContainer* apContainer, Messages::TESContainer& aContainer);
			void Deserialize(TESContainer* apContainer, const Messages::TESContainer& aContainer);

			void Serialize(TESSpellList* apTES, Messages::TESpellList& aMessage);
			void Deserialize(TESSpellList* apTES, const Messages::TESpellList& aMessage);

			void Serialize(TESNPC::FaceMorphs* apTES, Messages::FaceMorphs& aMessage);
			void Deserialize(TESNPC::FaceMorphs* apTES, const Messages::FaceMorphs& aMessage);

			void Serialize(TESNPC* apNpc, Messages::Npc& aNpc);
			void Deserialize(TESNPC* apNpc, const Messages::Npc& aNpc);
		}
	}
}