#include "stdafx.h"
#include "Test.hpp"

std::ofstream out;

__declspec(dllexport) void main()
{
	out.open("FreeScript.log", std::ios::trunc);
	out << "FreeScript Tests \n\n" << std::endl;
	RunActorDump();
	out.flush();
	out.close();
}