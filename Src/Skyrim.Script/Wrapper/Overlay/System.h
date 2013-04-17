#pragma once
#pragma managed

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

				static property bool CursorVisible
				{
					bool get();
					void set(bool);
				}

			private:
			};
		}
	}
}