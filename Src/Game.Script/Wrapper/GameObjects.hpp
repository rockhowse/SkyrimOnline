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
	};

	public interface class IActor : ITESObjectREFR
	{
	};
}
