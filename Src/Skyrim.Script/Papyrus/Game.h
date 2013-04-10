#pragma once

#include "../Wrapper/References.h"

namespace SkyrimScript
{
	namespace Papyrus
	{
		public ref class Game
		{
		public:

			static Wrapper::Actor^ GetPlayer();
		};
	}
}