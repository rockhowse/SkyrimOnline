#include "stdafx.h"
#include "Types.hpp"
#include "Memory.hpp"

namespace FreeScript
{
	String::String(const char* data)
	{
		((void(__thiscall*)(String*, const char*))0x00A50830)(this, data);
	}

	BSString::BSString(const char* d)
	{
		length = strlen(d);
		capacity = length;
		data = (char*)FormAllocate(capacity);
		strcpy_s(data, length, d);
	}

	BSString::~BSString()
	{
		FormFree(data);
		data = nullptr;
	}

	const char* BSString::Get()
	{
		return data;
	}
}