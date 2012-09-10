#pragma once

void Host(uint16_t pPort);
void Run();
void Drop();

namespace Skyrim
{
	namespace Logic
	{
		class MasterServer
		{
		public:

			typedef boost::shared_ptr<MasterServer> pointer;

			MasterServer();
			~MasterServer();

			void Run();
		};
	}
}