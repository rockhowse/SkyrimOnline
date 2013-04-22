#pragma once

struct InputListener
{
	virtual void OnPress(BYTE code) = 0;
	virtual void OnRelease(BYTE code) = 0;
	virtual void OnMousePress(BYTE code) = 0;
	virtual void OnMouseRelease(BYTE code) = 0;
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