#pragma once

#include <string>
#include <cstdint>

namespace Skyrim{
	namespace Entity
	{
		class Account
		{
		public:

			Account()
				:Banned(false),Id(0),Level(0)
			{
			}

			bool Banned;
			std::string Pass;
			std::string User;
			std::string Nicename;
			uint32_t Level;
			uint32_t Id;
		};
	}
}