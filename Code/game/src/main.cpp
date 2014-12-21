#include "GameServer.h"
#include <boost/thread.hpp>

int main()
{
	EnetServer::Initialize();
	try
	{
		g_pServer = new GameServer();
		while (true)
		{
			g_pServer->Update();
			boost::this_thread::yield();
		}
		delete g_pServer; g_pServer = nullptr;
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}

	delete g_pServer; g_pServer = nullptr;
    
	return 0;
}