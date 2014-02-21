#include "stdafx.h"
#include "Types.hpp"
#include "Memory.hpp"

namespace FreeScript
{
	BSFixedString::BSFixedString(const char* data)
	{
		((void(__thiscall*)(BSFixedString*, const char*))0xa511c0)(this, data);
	}

	BSString::BSString(const char* d)
	{
		length = strlen(d);
		capacity = length * 2;
		data = new char[capacity];
		strcpy_s(data, capacity, d); //created a more secure string copy with size capacity to prevent buffer overflow, used to be strcpy(data, d). Change back if desired
	}

	BSString::~BSString()
	{
		delete[] data;
		data = nullptr;
	}

	const char* BSString::Get()
	{
		return data;
	}
}