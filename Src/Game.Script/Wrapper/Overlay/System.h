#pragma once
#pragma managed

#include <Wrapper/IUpdatable.h>

namespace Game
{
	namespace Overlay
	{
		public ref class System
		{
		public:

			static void InjectKeyboardKey(unsigned char key, bool pressed);
			static void InjectMouseKey(unsigned char key, bool pressed);
			static void InjectMousePosition(unsigned int x, unsigned int y, unsigned int z);
			static void Register(Game::IUpdatable^ updatable);
			static void Unregister(Game::IUpdatable^ updatable);

			static property bool CursorVisible
			{
				bool get();
				void set(bool);
			}

		private:

			System();
		};
	}
}