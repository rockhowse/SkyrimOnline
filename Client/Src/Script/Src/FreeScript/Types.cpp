#include "stdafx.h"
#include "Types.hpp"
#include "Memory.hpp"

namespace FreeScript
{
	String::String(const char* data)
	{
		((void(__thiscall*)(String*, const char*))0xa511c0)(this, data);
	}

	BSString::BSString(const char* d)
	{
		length = strlen(d);
		capacity = length * 2;
		data = new char[capacity];
		strcpy(data, d);
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