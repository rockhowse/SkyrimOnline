#include "stdafx.h"
#include "MasterServer.h"

namespace Skyrim
{
	namespace Logic
	{
		MasterServer::MasterServer()
		{
			Host(27500);
		}

		MasterServer::~MasterServer()
		{
			Drop();
		}

		void MasterServer::Run()
		{
			::Run();
		}
	}
}