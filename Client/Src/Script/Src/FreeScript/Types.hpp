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
				return data[pIndex];
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

		class Iterator : public std::iterator<std::input_iterator_tag, item_type>
		{

			friend class List<item_type>;
			Iterator(Node* pHead) : mNode(pHead)
			{
			}

		public:

			Iterator& operator++()
			{
				if(!mNode)
					throw std::out_of_range("iterator is end.");
				mNode = mNode->next;
				return *this;
			}

			Iterator operator++(int)
			{
				Iterator tmp(*this);
				operator++();
				return tmp;
			}

			bool operator==(const Iterator& pItor)
			{
				return this->mNode == pItor->mNode;
			}

			bool operator!=(const Iterator& pItor)
			{
				return !(*this == pItor);
			}

			item_type* operator*()
			{
				if(!mNode)
					throw std::out_of_range("iterator is end.");
				return mNode->item;
			}

		private:

			Node* mNode;
		};

		Iterator begin()
		{
			return Iterator(&mHead);
		}

		Iterator end()
		{
			return Iterator(nullptr);
		}

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