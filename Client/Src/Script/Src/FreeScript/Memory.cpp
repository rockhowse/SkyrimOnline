#include "stdafx.h"
#include "Memory.hpp"

typedef void* (__thiscall *tAllocate)(void* pthis, uint32_t, uint32_t, bool);
typedef void (__thiscall *tFree)(void* pthis, void*, bool);

tAllocate oAllocator = (tAllocate)0xa483d0;
tFree oFree = (tFree)0xa47e20;

void* heap = (void*)0x1b40ba0;

void* FormAllocate(uint32_t size)
{
	return oAllocator(heap, size, 0, false);
}

void FormFree(void* ptr)
{
	oFree(heap, ptr, false);
}