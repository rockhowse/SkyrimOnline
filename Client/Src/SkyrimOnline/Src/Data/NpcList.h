#pragma once

namespace Skyrim
{
	namespace Data
	{
		class NpcList
		{
		public:

			class Iterator : public std::iterator<std::input_iterator_tag, TESNPC*>
			{
			public:

				Iterator(int pPos);
				Iterator(const Iterator& pItor);
				Iterator& operator++();
				Iterator& operator++(int);
				bool operator==(const Iterator& pItor);
				bool operator!=(const Iterator& pItor);
				TESNPC* operator*();

			private:

				uint32_t mPos;
			};

			static Iterator begin();
			static Iterator end();
			static uint32_t size();
		};
	}
}