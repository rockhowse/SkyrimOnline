#pragma once

#pragma unmanaged

#include <functional>

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

template <class Func>
class Signal
{
public:

	template <class T>
	void Add(T f)
	{
		mFunctions.push_back(f);
	}

	template <class... Args> 
	void operator()(Args... args)
	{
		for(auto itor : mFunctions)
		{
			itor(args...);
		}
	}

private:

	std::vector<std::function<Func>> mFunctions;
};