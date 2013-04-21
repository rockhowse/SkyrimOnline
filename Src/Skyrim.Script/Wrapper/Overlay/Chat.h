#pragma once
#pragma managed

namespace Skyrim
{
	namespace Script
	{
		namespace Overlay
		{
			public ref class Chat
			{
			public:

				Chat();
				~Chat();

				property bool Visible
				{
					bool get();
					void set(bool);
				}

			private:

				void* ptr;
			};
		}
	}
}