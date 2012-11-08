#include "stdafx.h"
#include "SkyrimWalker.hpp"

int main()
{
	try
	{
		std::ofstream rttiFile("rttiFile.hpp", std::ios::trunc);
		SkyrimWalker walker;
		rttiFile << walker.WalkRTTI();
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
	system("pause");
}