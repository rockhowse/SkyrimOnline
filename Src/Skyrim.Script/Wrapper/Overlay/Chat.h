#pragma once
#pragma managed

#include <Wrapper/IUpdatable.h>

namespace Skyrim
{
	namespace Script
	{
		namespace Overlay
		{
			public ref class Chat : public IUpdatable
			{
			public:

				Chat();
				~Chat();

				void Log(System::String^ pStr);

				property bool Visible
				{
					bool get();
					void set(bool);
				}
			};
		}
	}
}