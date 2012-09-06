#pragma once

#include "Forms.hpp"
#include "ExtraData.hpp"

namespace FreeScript
{
	class TESObjectREFR : public TESForm
	{
	public:

		template <class T>
		struct Vector
		{
			T X,Y,Z;
		};
		
		char pad14to24[0x24 - 0x14];

		TESForm* baseForm;
		Vector<float> rot;
		Vector<float> pos;

		TESObjectCELL	* parentCell;
		uint32_t		  pad;
		FreeScript::BaseExtraList	extraData;
		uint32_t          pad50;
	};

	class Actor : public ::FreeScript::TESObjectREFR
	{
	public:
		virtual ~Actor();

		char	pad54to19c[0x19C - 0x54];
	};
}