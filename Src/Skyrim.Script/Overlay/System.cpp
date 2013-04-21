#include "stdafx.h"
#include "System.h"
#include <Engine/Data.hpp>

#include <MyGUI/InputConverter.h>

#define MAP(a,b) if(vk == a) return b;

namespace Skyrim
{
	namespace Overlay
	{
		//--------------------------------------------------------------------------------
		System* TheSystem = nullptr;
		//--------------------------------------------------------------------------------
		System::System()
			:mPlatform(nullptr),mUI(nullptr)
		{
			mPlatform = new MyGUI::DirectXPlatform();
			mPlatform->initialise(TheIDirect3DDevice9);

			D3DDISPLAYMODE disp;

			TheIDirect3D9->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &disp);
			mPlatform->getRenderManagerPtr()->setViewSize(disp.Width, disp.Height);

			Setup();

			mUI = new MyGUI::Gui();
			mUI->initialise("MyGUI_Core.xml");

			SetCursor(false);
		}
		//--------------------------------------------------------------------------------
		System::~System()
		{

			if(mUI)
				mUI->shutdown();
			delete mUI; mUI = nullptr;
			if(mPlatform)
				mPlatform->shutdown();
			delete mPlatform;mPlatform = nullptr;
		}
		//--------------------------------------------------------------------------------
		void System::Setup()
		{

			MyGUI::xml::Document doc;

			if (!doc.open(std::string("resources.xml")))
				doc.getLastError();

			MyGUI::xml::ElementPtr root = doc.getRoot();
			if (root == nullptr || root->getName() != "Paths")
				return;

			MyGUI::xml::ElementEnumerator node = root->getElementEnumerator();
			while (node.next())
			{
				if (node->getName() == "Path")
				{
					bool root = false;
					if (node->findAttribute("root") != "")
					{
						root = MyGUI::utility::parseBool(node->findAttribute("root"));
						if (root) mRootMedia = node->getContent();
					}
					mPlatform->getDataManagerPtr()->addResourceLocation(node->getContent(), false);
				}
			}
		}
		//--------------------------------------------------------------------------------
		void System::Acquire()
		{
		}
		//--------------------------------------------------------------------------------
		void System::Reset()
		{
			mUI->destroyAllChildWidget();
		}
		//--------------------------------------------------------------------------------
		void System::Inject(uint8_t key, bool pressed)
		{
			if(mUI && mPlatform)
			{
				MyGUI::KeyCode code((MyGUI::KeyCode::Enum)key);
				if(pressed)
				{
					int c = input::ScanCodeToText(key);
					switch(key)
					{
					case MyGUI::KeyCode::Numpad7:
						c = '7';
						break;
					case MyGUI::KeyCode::Numpad8:
						c = '8';
						break;
					case MyGUI::KeyCode::Numpad9:
						c = '9';
						break;
					case MyGUI::KeyCode::Subtract:
						c = '-';
						break;
					case MyGUI::KeyCode::Numpad4:
						c = '4';
						break;
					case MyGUI::KeyCode::Numpad5:
						c = '5';
						break;
					case MyGUI::KeyCode::Numpad6:
						c = '6';
						break;
					case MyGUI::KeyCode::Add:
						c = '+';
						break;
					case MyGUI::KeyCode::Numpad1:
						c = '1';
						break;
					case MyGUI::KeyCode::Numpad2:
						c = '2';
						break;
					case MyGUI::KeyCode::Numpad3:
						c = '3';
						break;
					case MyGUI::KeyCode::Numpad0:
						c = '0';
						break;
					case MyGUI::KeyCode::Decimal:
						c = '.';
						break;
					}
					MyGUI::InputManager::getInstance().injectKeyPress(code,c);
				}
				else
					MyGUI::InputManager::getInstance().injectKeyRelease(code);
			}
		}
		//--------------------------------------------------------------------------------
		void System::InjectMouse(uint8_t key, bool pressed)
		{
			//Log::GetInstance()->Debug("Interface::InjectMouse() " + std::to_string((long long)key));
			if(mUI && mPlatform)
			{
				MyGUI::MouseButton code((MyGUI::MouseButton::Enum)key);
				if(pressed)
					MyGUI::InputManager::getInstance().injectMousePress(x,y,code);
				else
					MyGUI::InputManager::getInstance().injectMouseRelease(x,y,code);
			}
		}
		//--------------------------------------------------------------------------------
		void System::MouseMove(uint32_t px, uint32_t py, uint32_t pz)
		{
			//Log::GetInstance()->Debug("Interface::MouseMove()");
			if(mUI && mPlatform)
			{
				x = std::min<int32_t>(px, mUI->getViewWidth());
				y = std::min<int32_t>(py, mUI->getViewHeight());
				MyGUI::InputManager::getInstance().injectMouseMove(x,y,pz);
			}
		}
		//--------------------------------------------------------------------------------
		void System::SetCursor(bool pVisible)
		{
			if(mUI && mPlatform)
				mUI->setVisiblePointer(pVisible);
		}
		//--------------------------------------------------------------------------------
		bool System::IsCursorVisible()
		{
			if(mUI && mPlatform)
				return mUI->isVisiblePointer();
			return false;
		}
		//--------------------------------------------------------------------------------
		void System::OnRender(IDirect3DDevice9* pDevice)
		{
			//if(clock() - TheGameWorld->GetRendering() < 400)
			{
				IDirect3DStateBlock9* pStateBlock = NULL;
 				pDevice->CreateStateBlock(D3DSBT_ALL, &pStateBlock);
 				pStateBlock->Capture();
				try
				{
					if(mUI && mPlatform)
					{
						Update();
						mPlatform->getRenderManagerPtr()->drawOneFrame();
					}
				}
				catch(...)
				{
				}
				pStateBlock->Apply();
				pStateBlock->Release();
			}
		}
		//--------------------------------------------------------------------------------
		void System::OnLostDevice(IDirect3DDevice9* pDevice)
		{
			mPlatform->getRenderManagerPtr()->deviceLost();
		}
		//--------------------------------------------------------------------------------
		MyGUI::Gui* System::GetGui()
		{
			return mUI;
		}
		//--------------------------------------------------------------------------------
	}
}