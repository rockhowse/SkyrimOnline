#include "stdafx.h"
#include "SkyrimWalker.hpp"

int main()
{
	try
	{
		std::ofstream rttiFile("rttiFile.hpp", std::ios::trunc);
		std::ofstream singletonsFille("singletons.hpp", std::ios::trunc);
		SkyrimWalker walker;
		rttiFile << walker.WalkRTTI();
		singletonsFille << walker.WalkSingletons();

	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
	system("pause");
}