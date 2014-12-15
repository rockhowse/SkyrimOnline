#include "Memory.h"

typedef void* (__thiscall *tAllocate)(void* pthis, uint32_t, uint32_t, bool);
typedef void (__thiscall *tFree)(void* pthis, void*, bool);

tAllocate oAllocator = (tAllocate)0xa48d60;
tFree oFree = (tFree)0xa487b0;

void* heap = (void*)0x1b418b0;

void* FormAllocate(uint32_t size)
{
	return oAllocator(heap, size, 0, false);
}

void FormFree(void* ptr)
{
	oFree(heap, ptr, false);
}