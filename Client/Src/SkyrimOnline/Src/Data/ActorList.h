#pragma once

namespace Skyrim
{
	namespace Data
	{
		class ActorList
		{
		public:

			class Iterator : public std::iterator<std::input_iterator_tag, CActor*>
			{
			public:

				Iterator(int pPos);
				Iterator(const Iterator& pItor);
				Iterator& operator++();
				Iterator& operator++(int);
				bool operator==(const Iterator& pItor);
				bool operator!=(const Iterator& pItor);
				CActor* operator*();

			private:

				uint32_t mPos;
			};

			static Iterator begin();
			static Iterator end();
			static uint32_t size();
		};
	}
}