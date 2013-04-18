#pragma once

#include <Wrapper/References.h>

namespace Skyrim
{
	namespace Script
	{
		namespace Papyrus
		{
			public ref class Game
			{
			public:

				static Script::Actor^ GetPlayer();
				static property Script::TESForm^ Forms[UInt32]
				{
					Script::TESForm^ get(UInt32 aiFormID);
				}
			};
		}
	}
}