#pragma once

#pragma unmanaged

void HookDInput();
void ReleaseDInput();

struct InputListener
{
	virtual void OnPress(uint8_t code) = 0;
	virtual void OnRelease(uint8_t code) = 0;
	virtual void OnMousePress(uint8_t code) = 0;
	virtual void OnMouseRelease(uint8_t code) = 0;
	virtual void OnMouseMove(unsigned int x, unsigned int y, unsigned int z) = 0;
};

class IInputHook
{
public:

	virtual bool IsInputEnabled() = 0;
	virtual void SetInputEnabled(bool input) = 0;

	virtual InputListener* GetListener() = 0;
	virtual void SetListener(InputListener* listener) = 0;
};

extern IInputHook* TheIInputHook;