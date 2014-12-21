#include <Overlay\GUI.h>

namespace GameModule
{
	namespace Overlay
	{
		GUI* TheGUI = nullptr;

		GUI::GUI() : directXPlatform(nullptr), myGUI(nullptr)
		{
			this->directXPlatform = new MyGUI::DirectXPlatform();
			this->directXPlatform->initialise(gl_pmyIDirect3DDevice9);

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
				{
					this->directXPlatform->getRenderManagerPtr()->drawOneFrame();
				}
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
	}
}