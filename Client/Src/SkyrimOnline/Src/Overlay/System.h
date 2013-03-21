#pragma once

#include <Directx/myIDirect3DDevice9.h>

namespace Skyrim
{
	namespace Overlay
	{
		class Message;

		class System
		{
		public:

			System();
			~System();

			void Setup();

			void Inject(uint8_t key, bool pressed);
			void InjectMouse(uint8_t key, bool pressed);
			void MouseMove(uint32_t x, uint32_t y, uint32_t z);

			void SetCursor(bool pVisible);
			bool IsCursorVisible();

			void OnRender(myIDirect3DDevice9* pDevice);
			void OnLostDevice(myIDirect3DDevice9* pDevice);

			static System* GetInstance();
			MyGUI::Gui*	 GetGui();

			void Reset();
			void Acquire();

			template <class T>
			T* Instantiate()
			{
				return new T(mUI);
			}

		private:

			int32_t x,y;
			MyGUI::DirectXPlatform* mPlatform;
			MyGUI::Gui*				mUI;
			std::string mRootMedia;

			boost::signals::connection mRender,mReset;
		};

		extern System* TheSystem;
	}
}