#include "stdafx.h"
#include "Interface.h"
#include "Chat.h"
#include "Login.h"
#include "FriendList.h"
#include "ShardList.h"
#include "Message.h"
#include <SkyrimOnline.h>
#include <Directx/myIDirect3D9.h>
#include <InputConverter.h>

#define MAP(a,b) if(vk == a) return b;


namespace Skyrim
{
	namespace Overlay
	{
		//--------------------------------------------------------------------------------
		Interface* Interface::instance = nullptr;
		//--------------------------------------------------------------------------------
		Interface* Interface::GetInstance()
		{
			if(instance == nullptr)
				instance = new Interface;
			return instance;
		}
		//--------------------------------------------------------------------------------
		Interface::Interface()
			:mPlatform(nullptr),mUI(nullptr)
		{
			System::Log::Debug("Interface::ctor()");
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
		Interface::~Interface()
		{
			System::Log::Debug("Interface::dtor()");

			if(mUI)
				mUI->shutdown();
			delete mUI; mUI = nullptr;
			if(mPlatform)
				mPlatform->shutdown();
			delete mPlatform;mPlatform = nullptr;
		}
		//--------------------------------------------------------------------------------
		void Interface::Setup()
		{
			System::Log::Debug("Call to Interface::Setup()");
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
		void Interface::Acquire()
		{
			mMessageBox = boost::make_shared<Message>(mUI);
			mMessageBox->Hide();

			// UI needs its own context
			if(myIDirect3DDevice9::GetInstance())
			{
				mRender = myIDirect3DDevice9::GetInstance()->OnPresent.connect(std::bind(&Interface::OnRender, this, std::placeholders::_1));
				mReset = myIDirect3DDevice9::GetInstance()->OnReset.connect(std::bind(&Interface::OnLostDevice,this,std::placeholders::_1));
			}
			else
			{
				System::Log::Error("Unable to grab directx !");
				System::Log::Flush();
				exit(-1);
			}
		}
		//--------------------------------------------------------------------------------
		void Interface::Reset()
		{
			mRender.disconnect();
			mReset.disconnect();

			mUI->destroyAllChildWidget();
		}
		//--------------------------------------------------------------------------------
		void Interface::Inject(BYTE key, bool pressed)
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
		void Interface::InjectMouse(BYTE key, bool pressed)
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
		void Interface::MouseMove(unsigned int px, unsigned int py, unsigned int pz)
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
		void Interface::SetCursor(bool pVisible)
		{
			if(mUI && mPlatform)
				mUI->setVisiblePointer(pVisible);
		}
		//--------------------------------------------------------------------------------
		bool Interface::IsCursorVisible()
		{
			if(mUI && mPlatform)
				return mUI->isVisiblePointer();
			return false;
		}
		//--------------------------------------------------------------------------------
		void Interface::OnRender(myIDirect3DDevice9* pDevice)
		{
			if(clock() - SkyrimOnline::GetInstance().GetRendering() < 400)
			{
				try
				{
				}
				catch(...)
				{
				}
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
		void Interface::OnLostDevice(myIDirect3DDevice9* pDevice)
		{
			mPlatform->getRenderManagerPtr()->deviceLost();
		}
		//--------------------------------------------------------------------------------
		boost::shared_ptr<Message> Interface::GetMessage()
		{
			return mMessageBox;
		}
		//--------------------------------------------------------------------------------
		MyGUI::Gui* Interface::GetGui()
		{
			return mUI;
		}
		//--------------------------------------------------------------------------------
	}
}