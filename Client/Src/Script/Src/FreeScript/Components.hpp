#pragma once

#include "Types.hpp"

namespace FreeScript
{
	class BaseFormComponent
	{
	public:
		BaseFormComponent();
		virtual ~BaseFormComponent();

		virtual void Init();
	};

	class TESFullName : public ::FreeScript::BaseFormComponent
	{
	public:

		FreeScript::String name;
	};

	class BGSBipedObjectForm : public BaseFormComponent
	{
	public:

		enum
		{
			Head =		1 << 0,
			Hair =		1 << 1,
			Body =		1 << 2,
			Hands =		1 << 3,
			Forearms =	1 << 4,
			Amulet =	1 << 5,
			Ring =		1 << 6,
			Feet =		1 << 7,
			Calves =	1 << 8,
			Shield =	1 << 9,
			Unnamed10 =	1 << 10,
			LongHair =	1 << 11,
			Circlet =	1 << 12,
			Ears =		1 << 13,
			kPart_FX01 =1 << 31,
		};

		struct Data
		{
			uint32_t	parts;
			uint32_t	pad04to08;
		};

		Data	data;
	};
}