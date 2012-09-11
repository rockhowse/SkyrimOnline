#include "stdafx.h"
#include "InputManager.h"
#include <Directx/myIDirect3DDevice9.h>

namespace Skyrim
{
	namespace Engine
	{
		//--------------------------------------------------------------------------------
		InputManager::InputManager(InputManager::Listener& pListener)
			:mListener(pListener), mRun(true), mReset(true)
		{
			_trace

			Init();

			mThread = new boost::thread(std::bind(&InputManager::Run, this));
			myIDirect3DDevice9::GetInstance()->OnReset.connect(boost::bind(&InputManager::Reset, this, _1));
		}
		//--------------------------------------------------------------------------------
		void InputManager::Reset(myIDirect3DDevice9* pDevice)
		{
			mReset = true;
		}
		//--------------------------------------------------------------------------------
		void InputManager::Init()
		{
			// Valeur de retour des méthodes utilisées, permet la gestion des erreurs
			HRESULT result;

			// Création de l'objet DirectInput
			result = DirectInput8Create(
				myIDirect3DDevice9::GetInstance()->GetHinstance(),
				DIRECTINPUT_VERSION,
				IID_IDirectInput8,
				(void**)&mDirectInput,
				NULL
				);

			if(FAILED(result))
			{
				System::Log::Error("DirectInput8Create Failed.");
			}

			result  = mDirectInput->CreateDevice(
				GUID_SysKeyboard,
				&mKeyboard,
				NULL
				);

			if(FAILED(result))
			{
				System::Log::Error("Keyboard CreateDevice Failed.");
			}

			mKeyboard->SetDataFormat(
				&c_dfDIKeyboard
				);

			if(FAILED(result))
			{
				System::Log::Error("Mouse SetDataFormat Failed.");
			}

			result = mKeyboard->SetCooperativeLevel(
				myIDirect3DDevice9::GetInstance()->GetWindow(),
				DISCL_BACKGROUND | DISCL_NONEXCLUSIVE
				);

			if(FAILED(result))
			{
				System::Log::Error("Keyboard SetCooperativeLevel Failed.");
			}

			if(mKeyboard)
			{
				System::Log::Debug("Keyboard acquired !");
				mKeyboard->Acquire();
			}

			result  = mDirectInput->CreateDevice(
				GUID_SysMouse,
				&mMouse,
				NULL
				);

			if(FAILED(result))
			{
				System::Log::Error("Mouse CreateDevice Failed.");
			}

			result = mMouse->SetDataFormat(
				&c_dfDIMouse
				);

			if(FAILED(result))
			{
				System::Log::Error("Mouse SetDataFormat Failed.");
			}

			if(mMouse)
				mMouse->Acquire();

			for(auto i = 0 ; i < 256; ++i)
				mKeys[i] = 0;

			mReset = false;
		}
		//--------------------------------------------------------------------------------
		InputManager::~InputManager()
		{
			mRun = false;
			mThread->join();
			delete mThread;
			mMouse->Release();
			mKeyboard->Release();

			_trace
		}
		//--------------------------------------------------------------------------------
		void InputManager::Run()
		{
			while(mRun)
			{
				boost::this_thread::yield();
				if(mReset)
				{
					Init();
					continue;
				}

				DIMOUSESTATE tmp;
				char buffer[256];

				if(FAILED(mKeyboard->GetDeviceState(sizeof(buffer),(LPVOID)&buffer)))
				{
					mKeyboard->Acquire();
					break;
				}

				if(FAILED(mMouse->GetDeviceState(sizeof(DIMOUSESTATE),(LPVOID)&tmp)))
				{
					mMouse->Acquire();
					break;
				}

				mX += tmp.lX;
				mY += tmp.lY;

				for(auto i = 0 ; i < 256; ++i)
				{
					char state = buffer[i];
					if(state != mKeys[i])
					{
						mKeys[i] = buffer[i];
						if(buffer[i] & 0x80)
						{
							Event e;
							e.key = i;
							e.keyboard = true;
							e.pressed = true;
							e.time = clock();
							mBufferedInputs.push(e);
						}
						else
						{
							Event e;
							e.key = i;
							e.keyboard = true;
							e.pressed = false;
							e.time = clock();
							mBufferedInputs.push(e);
						}
					}
				}
				for(auto i = 0; i < 4; ++i)
				{
					char state = tmp.rgbButtons[i];
					if(state != mMouseState[i])
					{
						mMouseState[i] = state;
						if(state & 0x80)
						{
							Event e;
							e.key = i;
							e.keyboard = false;
							e.pressed = true;
							e.time = clock();
							mBufferedInputs.push(e);
						}
						else
						{
							Event e;
							e.key = i;
							e.keyboard = false;
							e.pressed = false;
							e.time = clock();
							mBufferedInputs.push(e);
						}
					}
				}
			}
		}
		//--------------------------------------------------------------------------------
		void InputManager::Update()
		{
			Event e;
			while(!mBufferedInputs.empty())
				while(mBufferedInputs.try_pop(e))
				{
					if((clock() - e.time) < 1000)
					{
						if(e.keyboard == true)
						{
							if(e.pressed == true)
								mListener.OnPress(e.key);
							else
								mListener.OnRelease(e.key);
						}
						else
						{
							if(e.pressed == true)
								mListener.OnMousePress(e.key);
							else
								mListener.OnMouseRelease(e.key);
						}
					}
				}

			POINT pos;
			GetCursorPos(&pos);
			mListener.OnMouseMove(pos.x,pos.y,0);
		}
		//--------------------------------------------------------------------------------
	}
}