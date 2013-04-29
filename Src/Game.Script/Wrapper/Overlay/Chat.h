#pragma once
#pragma managed

#include <Wrapper/IUpdatable.h>

namespace Game
{
	namespace Overlay
	{

		public ref class Chat : public Game::IUpdatable
		{
		public:

			delegate void InputHandler(System::String^);
			event InputHandler^ OnInput;

			Chat();
			~Chat();

			void Log(System::String^ pStr);

			property bool Visible
			{
				bool get();
				void set(bool);
			}

			void _inputHandle(const std::string& pStr);
		};
	}
}