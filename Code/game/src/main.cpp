#include "GameServer.h"
#include <boost/thread.hpp>
#include "BoostManager.h"

int main()
{
	try
	{
		g_pServer = new GameServer();
		while (true)
		{
			g_pServer->Update();
			boost::this_thread::yield();
		}
		delete g_pServer; g_pServer = 0;
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}

	delete g_pServer; g_pServer = 0;

	BoostManager::Destroy();
    
	return 0;
}