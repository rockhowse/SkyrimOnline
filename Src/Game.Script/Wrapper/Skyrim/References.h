#pragma once

#include "Forms.h"


namespace Skyrim
{
	namespace Script
	{
		public ref class TESObjectREFR : public Script::TESForm
		{
		public:

			TESObjectREFR(void* ptr);
			~TESObjectREFR();

			property Script::TESForm^ BaseForm
			{
				Script::TESForm^ get();
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

			Script::TESForm^ GetWornForm(System::UInt32 id);
			void EquipItem(Script::TESForm^ form);

			property Script::TESNPC^ BaseNpc
			{
				Script::TESNPC^ get();
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