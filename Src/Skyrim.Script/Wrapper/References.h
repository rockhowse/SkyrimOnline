#pragma once

#include "Forms.h"


namespace Game
{
	namespace Skyrim
	{
		public ref class TESObjectREFR : public Skyrim::TESForm
		{
		public:

			TESObjectREFR(void* ptr);
			~TESObjectREFR();

			property Skyrim::TESForm^ BaseForm
			{
				Skyrim::TESForm^ get();
			}

			property Microsoft::Xna::Framework::Vector3 Position
			{
				Microsoft::Xna::Framework::Vector3 get();
				void set(Microsoft::Xna::Framework::Vector3 pos);
			}

			property Microsoft::Xna::Framework::Vector3 Rotation
			{
				Microsoft::Xna::Framework::Vector3 get();
				void set(Microsoft::Xna::Framework::Vector3 pos);
			}
		};

		public ref class Actor : public TESObjectREFR
		{
		public:

			Actor(void* ptr);
			~Actor();

			void QueueNiNodeUpdate();

			void UnequipAll();

			Skyrim::TESForm^ GetWornForm(System::UInt32 id);
			void EquipItem(Skyrim::TESForm^ form);

			property Skyrim::TESNPC^ BaseNpc
			{
				Skyrim::TESNPC^ get();
			}

			property bool Dead
			{
				bool get();
			}

			property System::UInt32 Level
			{
				System::UInt32 get();
			}
		};
	}
}