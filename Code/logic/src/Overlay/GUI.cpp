#include <Overlay\GUI.h>
#include <InputConverter.h>

namespace Logic
{
	namespace Overlay
	{
		GUI* TheGUI = nullptr;

		GUI::GUI() : directXPlatform(nullptr), myGUI(nullptr)
		{
			this->directXPlatform = new MyGUI::DirectXPlatform();
			this->directXPlatform->initialise(g_pIDirect3DDevice9);

			this->directXPlatform->getDataManagerPtr()->addResourceLocation(".\\Data\\Online\\UI\\", false); // Add resource path for MyGUI.

			myGUI = new MyGUI::Gui();
			myGUI->initialise("MyGUI_Core.xml");

			this->setCursor(false);
		}

		GUI::~GUI()
		{
			if (this->myGUI != nullptr)
			{
				this->myGUI->shutdown();

				delete this->myGUI;
				this->myGUI = nullptr;
			}

			if (this->directXPlatform != nullptr)
			{
				this->directXPlatform->shutdown();

				delete this->directXPlatform;
				this->directXPlatform = nullptr;
			}
		}

		MyGUI::Gui* GUI::getGUI()
		{
			return this->myGUI;
		}

		void GUI::OnRender(IDirect3DDevice9* pDevice)
		{
			IDirect3DStateBlock9* pStateBlock = NULL;

			pDevice->CreateStateBlock(D3DSBT_ALL, &pStateBlock);
			pStateBlock->Capture();

			try
			{
				if (this->myGUI && this->directXPlatform)
					this->directXPlatform->getRenderManagerPtr()->drawOneFrame();
			}
			catch (...)
			{
			}

			pStateBlock->Apply();
			pStateBlock->Release();
		}

		void GUI::OnLostDevice(IDirect3DDevice9* pDevice)
		{
			this->directXPlatform->getRenderManagerPtr()->deviceLost();
		}

		void GUI::setCursor(bool Visible)
		{
			if (this->directXPlatform && this->myGUI)
				this->myGUI->setVisiblePointer(Visible);
		}
		std::ofstream as("tcode.txt");
		void GUI::InjectKey(unsigned char Key, bool isPressed)
		{
			if (this->directXPlatform == nullptr || this->myGUI == nullptr)
				return;

			MyGUI::KeyCode code((MyGUI::KeyCode::Enum)Key);

			if (isPressed == true)
			{
				int key = input::ScanCodeToText(Key);

				switch (Key)
				{
					case MyGUI::KeyCode::Decimal:
						key = '.';
						break;
					case MyGUI::KeyCode::Numpad0:
						key = '0';
						break;
					case MyGUI::KeyCode::Numpad1:
						key = '1';
						break;
					case MyGUI::KeyCode::Numpad2:
						key = '2';
						break;
					case MyGUI::KeyCode::Numpad3:
						key = '3';
						break;
					case MyGUI::KeyCode::Numpad4:
						key = '4';
						break;
					case MyGUI::KeyCode::Numpad5:
						key = '5';
						break;
					case MyGUI::KeyCode::Numpad6:
						key = '6';
						break;
					case MyGUI::KeyCode::Numpad7:
						key = '7';
						break;
					case MyGUI::KeyCode::Numpad8:
						key = '8';
						break;
					case MyGUI::KeyCode::Numpad9:
						key = '9';
						break;
					case MyGUI::KeyCode::Add:
						key = '+';
						break;
					case MyGUI::KeyCode::Subtract:
						key = '-';
						break;
					case MyGUI::KeyCode::Divide:
						key = '/';
						break;
				}

				this->myGUI->injectKeyPress(code, key);
			}
			else
				this->myGUI->injectKeyRelease(code);
		}

		void GUI::InjectMouse(unsigned char Key, bool isPressed)
		{
			if (this->directXPlatform == nullptr || this->myGUI == nullptr)
				return;

				MyGUI::MouseButton code((MyGUI::MouseButton::Enum)Key);

				if (isPressed)
					MyGUI::InputManager::getInstance().injectMousePress(this->PositionX, this->PositionY, code);
				else
					MyGUI::InputManager::getInstance().injectMouseRelease(this->PositionX, this->PositionY, code);
		}

		void GUI::MouseMove(unsigned int PositionX, unsigned int PositionY, unsigned int PositionZ)
		{
			if (this->directXPlatform == nullptr || this->myGUI == nullptr)
				return;

			this->PositionX = std::min<int>(PositionX, this->myGUI->getViewWidth());
			this->PositionY = std::min<int>(PositionY, this->myGUI->getViewHeight());

			MyGUI::InputManager::getInstance().injectMouseMove(PositionX, PositionY, PositionZ);
		}
	}
}