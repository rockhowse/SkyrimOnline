#pragma once

#pragma unmanaged

#include <functional>
#include <vector>

template <class Func>
struct Function
{
	typedef Func* type;
};


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
		for (auto itor : mFunctions)
		{
			itor(args...);
		}
	}

	private:

	std::vector<std::function<Func>> mFunctions;
};