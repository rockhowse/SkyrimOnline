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

		};

		public ref class Actor : public TESObjectREFR
		{
		public:

			Actor(void* ptr);
			~Actor();

			property Script::TESNPC^ BaseNpc
			{
				Script::TESNPC^ get();
			}
		};
	}
}