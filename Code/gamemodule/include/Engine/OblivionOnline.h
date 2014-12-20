#pragma once

#include <stdafx.h>

#include <Overlay\GUI.h>
#include <Overlay\Chat.h>

namespace GameModule
{
	namespace Engine
	{
		class OblivionOnline
		{
			public:
			
			OblivionOnline();

			void SetPlayerControls();

			private:

			typedef void(*tSetPlayerControls)(void);
			tSetPlayerControls setPlayerControls;
			
		};
	}
}