#pragma once

#include "Forms.h"


namespace Game
{
	namespace Skyrim
	{
		public ref class TESObjectREFR : public Skyrim::TESForm, ::Game::ITESObjectREFR
		{
		public:

			TESObjectREFR(void* ptr);
			~TESObjectREFR();

			virtual property ITESForm^ BaseForm
			{
				ITESForm^ get();
			}

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

		public ref class Actor : public TESObjectREFR, ::Game::IActor
		{
		public:

			Actor(void* ptr);
			~Actor();

			void QueueNiNodeUpdate();

			virtual void EnableAI(bool enabled);
			virtual void EquipItem(Game::ITESForm^ form);
			virtual void UnequipAll();

			Skyrim::TESForm^ GetWornForm(System::UInt32 id);
			
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