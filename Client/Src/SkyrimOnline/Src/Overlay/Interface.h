#pragma once

#include <Directx/myIDirect3DDevice9.h>

namespace Skyrim
{
	namespace Overlay
	{
		class Message;

		class Interface
		{
		public:

			void Setup();

			void Inject(BYTE key, bool pressed);
			void InjectMouse(BYTE key, bool pressed);
			void MouseMove(unsigned int x, unsigned int y, unsigned int z);

			void SetCursor(bool pVisible);
			bool IsCursorVisible();

			void OnRender(myIDirect3DDevice9* pDevice);
			void OnLostDevice(myIDirect3DDevice9* pDevice);

			boost::shared_ptr<Message>		GetMessage();

			static Interface* GetInstance();
			MyGUI::Gui*	 GetGui();

			void Reset();
			void Acquire();

		private:

			Interface();
			~Interface();

			int x,y;
			MyGUI::DirectXPlatform* mPlatform;
			MyGUI::Gui*				mUI;
			std::string mRootMedia;

			boost::shared_ptr<Message>		mMessageBox;

			static Interface* instance;

			boost::signals::connection mRender,mReset;
		};
	}
}