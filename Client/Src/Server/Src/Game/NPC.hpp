#pragma once

#include "Character.hpp"

namespace Skyrim
{
	namespace Game
	{
		class NPC : public Character
		{
		public:

			NPC();

			static void Register(class ScriptEngine* engine);

		private:

		};
	}
}