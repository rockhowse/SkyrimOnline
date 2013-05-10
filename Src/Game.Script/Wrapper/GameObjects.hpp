#pragma once
#pragma managed

#include "GameForms.hpp"

namespace Game
{
	public interface class ITESObjectREFR : ITESForm
	{
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

		property ITESForm^ BaseForm
		{
			ITESForm^ get();
		}
	};

	public interface class IActor : ITESObjectREFR
	{
		void EnableAI(bool enabled);
		void EquipItem(ITESForm^ form);
		void UnequipAll();
	};
}
