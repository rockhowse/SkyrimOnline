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

			void Inject(BYTE key, bool pressed);
			void InjectMouse(BYTE key, bool pressed);
			void MouseMove(unsigned int x, unsigned int y, unsigned int z);

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

			int x,y;
			MyGUI::DirectXPlatform* mPlatform;
			MyGUI::Gui*				mUI;
			std::string mRootMedia;

			boost::signals::connection mRender,mReset;
		};

		extern System* TheSystem;
	}
}