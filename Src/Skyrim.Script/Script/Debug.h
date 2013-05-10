#pragma once

namespace Game
{
	namespace Script
	{
		namespace Skyrim
		{
			public ref class Debug
			{
			public:

				static void Notification(System::String^ str);
				static void SendAnimationEvent(::Game::IActor^ arRef, System::String^ asEventName);
			};
		}
	}
}