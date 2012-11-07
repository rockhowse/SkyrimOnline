#include "stdafx.h"
#include "System.h"

#include <GameWorld.h>
#include <Directx/myIDirect3D9.h>
#include <InputConverter.h>

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
			_trace
			mPlatform = new MyGUI::DirectXPlatform();
			mPlatform->initialise(myIDirect3DDevice9::GetInstance()->GetDevice());

			D3DDISPLAYMODE disp;
			IDirect3D9* d3d;
			myIDirect3DDevice9::GetInstance()->GetDirect3D(&d3d);

			d3d->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &disp);
			mPlatform->getRenderManagerPtr()->setViewSize(disp.Width, disp.Height);

			Setup();

			mUI = new MyGUI::Gui();
			mUI->initialise("MyGUI_Core.xml");
		}
		//--------------------------------------------------------------------------------
		System::~System()
		{
			_trace

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
			_trace

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
			// UI needs its own context
			if(myIDirect3DDevice9::GetInstance())
			{
				mRender = myIDirect3DDevice9::GetInstance()->OnPresent.connect(std::bind(&System::OnRender, this, std::placeholders::_1));
				mReset = myIDirect3DDevice9::GetInstance()->OnReset.connect(std::bind(&System::OnLostDevice,this,std::placeholders::_1));
			}
			else
			{
				Framework::System::Log::Error("Unable to grab directx !");
				Framework::System::Log::Flush();
				exit(-1);
			}
		}
		//--------------------------------------------------------------------------------
		void System::Reset()
		{
			mRender.disconnect();
			mReset.disconnect();

			mUI->destroyAllChildWidget();
		}
		//--------------------------------------------------------------------------------
		void System::Inject(BYTE key, bool pressed)
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
		void System::InjectMouse(BYTE key, bool pressed)
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
		void System::MouseMove(unsigned int px, unsigned int py, unsigned int pz)
		{
			//Log::GetInstance()->Debug("Interface::MouseMove()");
			if(mUI && mPlatform)
			{
				x = std::min<int>(px, mUI->getViewWidth());
				y = std::min<int>(py, mUI->getViewHeight());
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
		void System::OnRender(myIDirect3DDevice9* pDevice)
		{
			if(clock() - TheGameWorld->GetRendering() < 400)
			{
				IDirect3DStateBlock9* pStateBlock = NULL;
 				pDevice->CreateStateBlock(D3DSBT_ALL, &pStateBlock);
 				pStateBlock->Capture();
				try
				{
					if(mUI && mPlatform)
					{
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
		void System::OnLostDevice(myIDirect3DDevice9* pDevice)
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