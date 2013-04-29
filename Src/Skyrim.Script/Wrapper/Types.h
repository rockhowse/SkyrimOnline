#pragma once

#pragma unmanaged
#include <FreeScript/Types.hpp>
#pragma managed

namespace Game
{
	namespace Skyrim
	{
		public ref class BSFixedString
		{
		private:

			void* ptr;

		public:

			BSFixedString(FreeScript::BSFixedString* ptr);
			~BSFixedString();

			virtual System::String^ ToString() override;

		};
	}
}