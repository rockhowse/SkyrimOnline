#pragma once
#pragma managed

#include <Wrapper/IUpdatable.h>

namespace Skyrim
{
	namespace Script
	{
		namespace Overlay
		{
			public ref class System
			{
			public:

				static void InjectKeyboardKey(unsigned char key, bool pressed);
				static void InjectMouseKey(unsigned char key, bool pressed);
				static void InjectMousePosition(unsigned int x, unsigned int y, unsigned int z);
				static void Register(Skyrim::Script::IUpdatable^ updatable);
				static void Unregister(Skyrim::Script::IUpdatable^ updatable);

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
}