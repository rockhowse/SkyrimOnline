#pragma once

#include "GameForms.h"

using namespace System;

namespace Game
{
	namespace Oblivion
	{
		public ref class TESObjectREFR : public Oblivion::TESForm
		{
		public:

			TESObjectREFR(void * ptr);
			~TESObjectREFR();
		};

		public ref class MobileObject : public Oblivion::TESObjectREFR
		{
		public:

			MobileObject(void * ptr);
			~MobileObject();
		};

		public ref class Actor : public Oblivion::MobileObject
		{
		public:

			Actor(void* ptr);
			~Actor();

		};
	}
}