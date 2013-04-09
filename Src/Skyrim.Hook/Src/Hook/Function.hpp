#pragma once

#pragma unmanaged

template <class Func>
struct Function
{
	typedef Func* type;
};

#define NAKED_JUMP(f) \
	__declspec(naked) void __stdcall f##_naked() \
{ __asm pop eax __asm push ecx __asm push eax  __asm jmp f }

#define THISCALLVOID void* _this, void* fastcall
#define THISCALL(name) name* _this, void* fastcall