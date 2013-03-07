#pragma once

void* fGetAngleX = (void*)0x902600;
void* fGetAngleY = (void*)0x902620;
void* fGetAngleZ = (void*)0x902640;

template <class T>
class Callable
{
	static void Call(void* addr, void* arg)
	{
		int a, b;
		((T*)addr)(a,b,arg);
	}
};


template <class T>
static void Invoke(T* arg)
{
	Callable<double(int, int,void*)>::Call(fGetAngleX, 4);
}