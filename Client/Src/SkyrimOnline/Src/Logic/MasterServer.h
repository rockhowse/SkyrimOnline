#pragma once

void* Host(uint16_t pPort);
void Run(void* ptr);
void Drop(void* ptr);

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
		private:

			void* mImpl;
		};
	}
}