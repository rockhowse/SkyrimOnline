#define _CRT_SECURE_NO_WARNINGS

#include <Logic/World.h>
#include <System/Log.h>
#include <Crypt/RSA.h>

/*int main()
{
	try
	{
		Skyrim::Crypt::RSA::Init();
		auto world = boost::make_shared<Skyrim::Logic::World>(27500);
	}
	catch (std::exception& e)
	{
		Skyrim::System::Log::Error(e.what());
	}
	Skyrim::System::Log::Flush();

	system("pause");
	return 0;
}*/