#pragma once

#include <Directx/myIDirect3DDevice9.h>

struct InputListener
{
	virtual void OnPress(BYTE code) = 0;
	virtual void OnRelease(BYTE code) = 0;
	virtual void OnMousePress(BYTE code) = 0;
	virtual void OnMouseRelease(BYTE code) = 0;
	virtual void OnMouseMove(unsigned int x, unsigned int y, unsigned int z) = 0;
};

class __declspec(dllimport) InputHook
{
public:

	static InputHook* GetInstance();

	bool IsInputEnabled();
	void SetInputEnabled(bool input);

	InputListener* GetListener();
	void SetListener(InputListener* listener);

private:

	InputHook();

	bool mEnabled;	
	InputListener* mListener;
};
