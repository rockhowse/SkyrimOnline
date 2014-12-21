#include <stdafx.h>

#include <DInput\Input.hpp>
#include <WinAPI.hpp>

#pragma unmanaged

#define IMPL_DEFINE_GUID(name, l, w1, w2, b1, b2, b3, b4, b5, b6, b7, b8) \
	EXTERN_C const GUID name \
	= { l, w1, w2, { b1, b2,  b3,  b4,  b5,  b6,  b7,  b8 } }

IMPL_DEFINE_GUID(GUID_SysMouse, 0x6F1D2B60, 0xD5A0, 0x11CF, 0xBF, 0xC7, 0x44, 0x45, 0x53, 0x54, 0x00, 0x00);
IMPL_DEFINE_GUID(GUID_SysKeyboard, 0x6F1D2B61, 0xD5A0, 0x11CF, 0xBF, 0xC7, 0x44, 0x45, 0x53, 0x54, 0x00, 0x00);

typedef HRESULT (_stdcall * DirectInput8Create_t)(HINSTANCE, DWORD, REFIID, LPVOID, LPUNKNOWN);
static DirectInput8Create_t	DirectInput8Create_r;

IInputHook* TheIInputHook = nullptr;

class InputHook : public IInputHook
{
public:

	static InputHook* GetInstance()
	{
		if (TheIInputHook == nullptr)
			TheIInputHook = new InputHook;

		return (InputHook*)TheIInputHook;
	}

	bool IsInputEnabled()
	{
		return mEnabled;
	}

	void SetInputEnabled(bool input)
	{
		mEnabled = input;
	}

	InputListener* GetListener()
	{
		return mListener;
	}

	void SetListener(InputListener* listener)
	{
		mListener = listener;
	}

private:

	InputHook() : mEnabled(true), mListener(nullptr)
	{

	}

	bool mEnabled;
	InputListener* mListener;
};

class myDirectInputDevice : public IDirectInputDevice8A
{
public:
	myDirectInputDevice(IDirectInputDevice8A * device, bool keyboard)
		:mRealDevice(device), mKeyboard(keyboard)
	{
		memset(mBuffer, 0, 256);
	}

	HRESULT _stdcall QueryInterface(REFIID riid, LPVOID * ppvObj)
	{
		return mRealDevice->QueryInterface(riid, ppvObj);
	}

	ULONG _stdcall AddRef(void)
	{
		return mRealDevice->AddRef();
	}

	ULONG _stdcall Release(void)
	{
		ULONG count = mRealDevice->Release();

		if (count == 0)
		{
			delete this;
			return 0;
		}
		return count;
	}

	// IDirectInputDevice8A
	HRESULT _stdcall GetCapabilities(LPDIDEVCAPS a) { return mRealDevice->GetCapabilities(a); }
	HRESULT _stdcall EnumObjects(LPDIENUMDEVICEOBJECTSCALLBACKA a, LPVOID b, DWORD c) { return mRealDevice->EnumObjects(a, b, c); }
	HRESULT _stdcall GetProperty(REFGUID a, DIPROPHEADER* b) { return mRealDevice->GetProperty(a, b); }
	HRESULT _stdcall SetProperty(REFGUID a, const DIPROPHEADER* b) { return mRealDevice->SetProperty(a, b); }
	HRESULT _stdcall Acquire(void) { return mRealDevice->Acquire(); }
	HRESULT _stdcall Unacquire(void) { return mRealDevice->Unacquire(); }

	HRESULT _stdcall GetDeviceState(DWORD outDataLen, LPVOID outData)
	{
		if (mKeyboard)
		{
			uint8_t	buffer[256] = { 0 };
			HRESULT ret = mRealDevice->GetDeviceState(256, buffer);
			if (ret != DI_OK)
				return ret;

			for (auto i = 0; i < 256; ++i)
			{

				if (buffer[i] != mBuffer[i])
				{
					mBuffer[i] = buffer[i];

					if (buffer[i] & 0x80)
					{
						if (InputHook::GetInstance()->GetListener())
							InputHook::GetInstance()->GetListener()->OnPress(i);
					}
					else
					{
						if (InputHook::GetInstance()->GetListener())
							InputHook::GetInstance()->GetListener()->OnRelease(i);
					}
				}
			}


			if (InputHook::GetInstance()->IsInputEnabled() == false)
				memset(buffer, 0, 256);

			memcpy(outData, buffer, outDataLen < 256 ? outDataLen : 256);

			return ret;
		}
		else
		{
			POINT pos;
			GetCursorPos(&pos);
			if (InputHook::GetInstance()->GetListener())
				InputHook::GetInstance()->GetListener()->OnMouseMove(pos.x, pos.y, 0);

			HRESULT ret = mRealDevice->GetDeviceState(outDataLen, outData);

			if (ret != DI_OK)
				return ret;

			DIMOUSESTATE2* mouseState = (DIMOUSESTATE2*)outData;
			for (auto i = 0; i < 4; ++i)
			{
				char state = mouseState->rgbButtons[i];
				if (state != mBuffer[i])
				{
					mBuffer[i] = state;
					if (state & 0x80)
					{
						if (InputHook::GetInstance()->GetListener())
							InputHook::GetInstance()->GetListener()->OnMousePress(i);
					}
					else
					{
						if (InputHook::GetInstance()->GetListener())
							InputHook::GetInstance()->GetListener()->OnMouseRelease(i);
					}
				}
			}
			return ret;
		}

	}

	HRESULT _stdcall GetDeviceData(DWORD dataSize, DIDEVICEOBJECTDATA * outData, DWORD * outDataLen, DWORD flags)
	{
		HRESULT ret = mRealDevice->GetDeviceData(dataSize, outData, outDataLen, flags);
		/*if(outData)
			for(uint32_t i = 0 ; i < *outDataLen; ++i)
			{
			if(outData[i].dwData & 0x80)
			{
			if(InputHook::GetInstance()->GetListener())
			InputHook::GetInstance()->GetListener()->OnPress(outData[i].dwOfs);
			}
			else
			{
			if(InputHook::GetInstance()->GetListener())
			InputHook::GetInstance()->GetListener()->OnRelease(outData[i].dwOfs);
			}
			}

			if(InputHook::GetInstance()->IsInputEnabled() == false)
			{
			*outDataLen = 0;
			}*/


		return ret;
	}

	HRESULT _stdcall SetDataFormat(const DIDATAFORMAT* a) { return mRealDevice->SetDataFormat(a); }
	HRESULT _stdcall SetEventNotification(HANDLE a) { return mRealDevice->SetEventNotification(a); }
	HRESULT _stdcall SetCooperativeLevel(HWND a, DWORD b) { return mRealDevice->SetCooperativeLevel(a, b); }
	HRESULT _stdcall GetObjectInfo(LPDIDEVICEOBJECTINSTANCEA a, DWORD b, DWORD c) { return mRealDevice->GetObjectInfo(a, b, c); }
	HRESULT _stdcall GetDeviceInfo(LPDIDEVICEINSTANCEA a) { return mRealDevice->GetDeviceInfo(a); }
	HRESULT _stdcall RunControlPanel(HWND a, DWORD b) { return mRealDevice->RunControlPanel(a, b); }
	HRESULT _stdcall Initialize(HINSTANCE a, DWORD b, REFGUID c) { return mRealDevice->Initialize(a, b, c); }
	HRESULT _stdcall CreateEffect(REFGUID a, LPCDIEFFECT b, LPDIRECTINPUTEFFECT *c, LPUNKNOWN d) { return mRealDevice->CreateEffect(a, b, c, d); }
	HRESULT _stdcall EnumEffects(LPDIENUMEFFECTSCALLBACKA a, LPVOID b, DWORD c) { return mRealDevice->EnumEffects(a, b, c); }
	HRESULT _stdcall GetEffectInfo(LPDIEFFECTINFOA a, REFGUID b) { return mRealDevice->GetEffectInfo(a, b); }
	HRESULT _stdcall GetForceFeedbackState(LPDWORD a) { return mRealDevice->GetForceFeedbackState(a); }
	HRESULT _stdcall SendForceFeedbackCommand(DWORD a) { return mRealDevice->SendForceFeedbackCommand(a); }
	HRESULT _stdcall EnumCreatedEffectObjects(LPDIENUMCREATEDEFFECTOBJECTSCALLBACK a, LPVOID b, DWORD c) { return mRealDevice->EnumCreatedEffectObjects(a, b, c); }
	HRESULT _stdcall Escape(LPDIEFFESCAPE a) { return mRealDevice->Escape(a); }
	HRESULT _stdcall Poll(void) { return mRealDevice->Poll(); }
	HRESULT _stdcall SendDeviceData(DWORD a, LPCDIDEVICEOBJECTDATA b, LPDWORD c, DWORD d) { return mRealDevice->SendDeviceData(a, b, c, d); }
	HRESULT _stdcall EnumEffectsInFile(LPCSTR a, LPDIENUMEFFECTSINFILECALLBACK b, LPVOID c, DWORD d) { return mRealDevice->EnumEffectsInFile(a, b, c, d); }
	HRESULT _stdcall WriteEffectToFile(LPCSTR a, DWORD b, LPDIFILEEFFECT c, DWORD d) { return mRealDevice->WriteEffectToFile(a, b, c, d); }
	HRESULT _stdcall BuildActionMap(LPDIACTIONFORMATA a, LPCSTR b, DWORD c) { return mRealDevice->BuildActionMap(a, b, c); }
	HRESULT _stdcall SetActionMap(LPDIACTIONFORMATA a, LPCSTR b, DWORD c) { return mRealDevice->SetActionMap(a, b, c); }
	HRESULT _stdcall GetImageInfo(LPDIDEVICEIMAGEINFOHEADERA a) { return mRealDevice->GetImageInfo(a); }


private:
	IDirectInputDevice8A * mRealDevice;
	bool mKeyboard;
	uint8_t mBuffer[256];
};

class myDirectInput : public IDirectInput8A
{
	public:

	myDirectInput(IDirectInput8A * obj) : mRealInput(obj)
	{
	}

	HRESULT _stdcall QueryInterface(REFIID riid, LPVOID* ppvObj) { return mRealInput->QueryInterface(riid, ppvObj); }

	ULONG _stdcall AddRef(void)
	{
		return mRealInput->AddRef();
	}

	ULONG _stdcall Release(void)
	{
		ULONG count = mRealInput->Release();

		if (count == 0)
		{
			delete this;
			return 0;
		}

		return count;
	}

	HRESULT _stdcall CreateDevice(REFGUID typeGuid, IDirectInputDevice8A ** device, IUnknown * unused)
	{
		if (typeGuid != GUID_SysKeyboard && typeGuid != GUID_SysMouse)
		{
			return mRealInput->CreateDevice(typeGuid, device, unused);
		}
		else
		{
			IDirectInputDevice8A	* dev;

			HRESULT hr = mRealInput->CreateDevice(typeGuid, &dev, unused);
			if (hr != DI_OK) return hr;

			*device = new myDirectInputDevice(dev, typeGuid == GUID_SysKeyboard);

			return hr;
		}
	}

	HRESULT _stdcall EnumDevices(DWORD a, LPDIENUMDEVICESCALLBACKA b, void* c, DWORD d) { return mRealInput->EnumDevices(a, b, c, d); }
	HRESULT _stdcall GetDeviceStatus(REFGUID r) { return mRealInput->GetDeviceStatus(r); }
	HRESULT _stdcall RunControlPanel(HWND a, DWORD b) { return mRealInput->RunControlPanel(a, b); }
	HRESULT _stdcall Initialize(HINSTANCE a, DWORD b) { return mRealInput->Initialize(a, b); }
	HRESULT _stdcall FindDevice(REFGUID a, LPCSTR b, LPGUID c) { return mRealInput->FindDevice(a, b, c); }
	HRESULT _stdcall EnumDevicesBySemantics(LPCSTR a, LPDIACTIONFORMATA b, LPDIENUMDEVICESBYSEMANTICSCBA c, void* d, DWORD e) { return mRealInput->EnumDevicesBySemantics(a, b, c, d, e); }
	HRESULT _stdcall ConfigureDevices(LPDICONFIGUREDEVICESCALLBACK a, LPDICONFIGUREDEVICESPARAMSA b, DWORD c, void* d) { return mRealInput->ConfigureDevices(a, b, c, d); }

	private:
	IDirectInput8A	* mRealInput;
	ULONG mReferences;
};

static HRESULT _stdcall DirectInput8Create_c(HINSTANCE instance, DWORD version, REFIID iid, void * out, IUnknown * outer)
{
	IDirectInput8A * dinput;
	HRESULT hr = DirectInput8Create_r(instance, version, iid, &dinput, outer);

	if (hr != DI_OK) 
		return hr;

	*((IDirectInput8A**)out) = new myDirectInput(dinput);

	return DI_OK;
}

HINSTANCE g_directInput = 0;

void HookDInput()
{
	if (!g_directInput)
		g_directInput = ::LoadLibraryA("dinput8.dll");

	DirectInput8Create_r = (DirectInput8Create_t)GetProcAddress(g_directInput, "DirectInput8Create");
	Mhook_SetHook((PVOID*)&DirectInput8Create_r, DirectInput8Create_c);

}

void ReleaseDInput()
{
	if(g_directInput)
		::FreeLibrary(g_directInput);

	Mhook_Unhook((PVOID*)DirectInput8Create_c);
}