#pragma once

#include "GameForms.h"

using namespace System;

namespace Game
{
	namespace Oblivion
	{
		public ref class TESObjectREFR : public Oblivion::TESForm, ::Game::ITESObjectREFR
		{
		public:

			TESObjectREFR(void * ptr);
			~TESObjectREFR();

			virtual property Microsoft::Xna::Framework::Vector3 Position
			{
				Microsoft::Xna::Framework::Vector3 get();
				void set(Microsoft::Xna::Framework::Vector3 pos);
			}

			virtual property Microsoft::Xna::Framework::Vector3 Rotation
			{
				Microsoft::Xna::Framework::Vector3 get();
				void set(Microsoft::Xna::Framework::Vector3 pos);
			}
		};

		public ref class MobileObject : public Oblivion::TESObjectREFR
		{
		public:

			MobileObject(void * ptr);
			~MobileObject();
		};

		public ref class Actor : public Oblivion::MobileObject, ::Game::IActor
		{
		public:

			Actor(void* ptr);
			~Actor();

		};
	}
}