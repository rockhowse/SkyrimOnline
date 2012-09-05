#pragma once

namespace FreeScript
{
	template <class T>
	class Vector
	{
	public:

		T* data;
		uint32_t capacity;
		uint32_t size;

		Vector() : size(0), capacity(0), data(nullptr) {};

		T& operator[](uint32_t pIndex)
		{
			if(pIndex < size)
				return set[pIndex];
			throw std::runtime_error("Out of range !");
		}
	};

	class String
	{
	public:

		const char* data;

		String(const char* data);
	};
}