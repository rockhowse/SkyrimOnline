#include "stdafx.h"
#include "MasterServer.h"

namespace Skyrim
{
	namespace Logic
	{
		MasterServer::MasterServer()
		{
			_trace
			mImpl = Host(27500);
		}

		MasterServer::~MasterServer()
		{
			_trace
			Drop(mImpl);
		}

		void MasterServer::Run()
		{
			::Run(mImpl);
		}
	}
}