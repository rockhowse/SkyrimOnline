#pragma once

#include "Forms.h"

namespace Skyrim
{
	namespace Script
	{
		public value struct Vector3
		{
		public:
			float X,Y,Z;
		};

		public ref class TESObjectREFR : public Script::TESForm
		{
		public:

			TESObjectREFR(void* ptr);
			~TESObjectREFR();

			property Script::TESForm^ BaseForm
			{
				Script::TESForm^ get();
			}

			property Vector3 Position
			{
				Vector3 get();
				void set(Vector3 pos);
			}

			property Vector3 Rotation
			{
				Vector3 get();
				void set(Vector3 pos);
			}
		};

		public ref class Actor : public TESObjectREFR
		{
		public:

			Actor(void* ptr);
			~Actor();

			void QueueNiNodeUpdate();

			void UnequipAll();

			property Script::TESNPC^ BaseNpc
			{
				Script::TESNPC^ get();
			}

			property bool Dead
			{
				bool get();
			}

			property UInt32 Level
			{
				UInt32 get();
			}

			property Script::TESForm^ WornForms[UInt32]
			{
				Script::TESForm^ get(UInt32 id);
				void set(UInt32 id, Script::TESForm^ form);
			}
		};
	}
}