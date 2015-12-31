#include <Overlay\GUI.h>
#include <InputConverter.h>


GUI* TheGUI = nullptr;

GUI::GUI() : m_pPlatform(nullptr), myGUI(nullptr)
{
	m_pPlatform = new MyGUI::DirectXPlatform();
	m_pPlatform->initialise(g_pIDirect3DDevice9);

	m_pPlatform->getDataManagerPtr()->addResourceLocation(".\\Data\\Online\\UI\\", false); // Add resource path for MyGUI.

	D3DDISPLAYMODE disp;
	g_pIDirect3D9->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &disp);
	m_pPlatform->getRenderManagerPtr()->setViewSize(disp.Width, disp.Height);

	myGUI = new MyGUI::Gui();
	myGUI->initialise("MyGUI_Core.xml");

	this->SetCursor(false);
}

GUI::~GUI()
{
	if (this->myGUI != nullptr)
	{
		this->myGUI->shutdown();

		delete this->myGUI;
		this->myGUI = nullptr;
	}

	if (this->m_pPlatform != nullptr)
	{
		this->m_pPlatform->shutdown();

		delete this->m_pPlatform;
		this->m_pPlatform = nullptr;
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
		if (this->myGUI && this->m_pPlatform)
			this->m_pPlatform->getRenderManagerPtr()->drawOneFrame();
	}
	catch (...)
	{
	}

	pStateBlock->Apply();
	pStateBlock->Release();
}

void GUI::OnLostDevice(IDirect3DDevice9* pDevice)
{
	try
	{
		this->m_pPlatform->getRenderManagerPtr()->deviceLost();
	}
	catch (MyGUI::Exception& exception)
	{

	}
			
}
		
void GUI::SetCursor(bool Visible)
{
	if (this->m_pPlatform && this->myGUI)
		this->myGUI->setVisiblePointer(Visible);
}

void GUI::InjectKey(unsigned char Key, bool isPressed)
{
	if (this->m_pPlatform == nullptr || this->myGUI == nullptr)
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

		if (MyGUI::InputManager::getInstance().isShiftPressed())
		{
			key = toupper(key);
		}

		MyGUI::InputManager::getInstance().injectKeyPress(code, key);
	}
	else
		MyGUI::InputManager::getInstance().injectKeyRelease(code);
}

void GUI::InjectMouse(unsigned char Key, bool isPressed)
{
	if (this->m_pPlatform == nullptr || this->myGUI == nullptr)
		return;

		MyGUI::MouseButton code((MyGUI::MouseButton::Enum)Key);

		if (isPressed)
			MyGUI::InputManager::getInstance().injectMousePress(this->PositionX, this->PositionY, code);
		else
			MyGUI::InputManager::getInstance().injectMouseRelease(this->PositionX, this->PositionY, code);
}

void GUI::MouseMove(unsigned int PositionX, unsigned int PositionY, unsigned int PositionZ)
{
	if (this->m_pPlatform == nullptr || this->myGUI == nullptr)
		return;

	this->PositionX = std::min<int>(PositionX, this->myGUI->getViewWidth());
	this->PositionY = std::min<int>(PositionY, this->myGUI->getViewHeight());

	MyGUI::InputManager::getInstance().injectMouseMove(PositionX, PositionY, PositionZ);
}
