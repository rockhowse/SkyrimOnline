#include "stdafx.h"
#include "NPC.hpp"
#include "ScriptEngine.hpp"

namespace Skyrim
{
	namespace Game
	{
		//--------------------------------------------------------------------------------
		NPC::NPC()
		{

		}
		//--------------------------------------------------------------------------------
		void NPC::Register(class ScriptEngine* engine)
		{
			engine->RegisterReferenceClass(NPC);
			engine->RegisterInheritance(Character, NPC);
		}
		//--------------------------------------------------------------------------------
		//--------------------------------------------------------------------------------
	}
}