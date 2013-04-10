#pragma once

#include "Forms.h"

namespace SkyrimScript
{
	namespace Wrapper
	{
		public ref class TESObjectREFR : public Wrapper::TESForm
		{
		public:

			TESObjectREFR(void* ptr);
			~TESObjectREFR();

			property Wrapper::TESForm^ BaseForm
			{
				Wrapper::TESForm^ get();
			}

		};

		public ref class Actor : public Wrapper::TESObjectREFR
		{
		public:

			Actor(void* ptr);
			~Actor();
		};
	}
}