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

	template <class T>
	class List
	{
		typedef typename T item_type;
		struct Node {

			item_type*	item;
			Node*		next;
		};

		Node mHead;

	public:

		Node* Head() 
		{
			return &mHead;
		}

		item_type* At(const int32_t pIndex)
		{
			int32_t i = 0;
			for(auto node = Head(); node && node->item; node = node->next, ++i)
			{
				if(i == pIndex)
					return node->item;
			}
			return nullptr;
		}
	};

	class String
	{
	public:

		const char* data;

		String(const char* data);
	};
}