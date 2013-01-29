#include "stdafx.h"
#include <GameWorld.h>
#include <Script/Online.h>
#include <Logic/Session.h>

int GenerateDump(EXCEPTION_POINTERS* pExceptionPointers)
{
	BOOL bMiniDumpSuccessful;
	TCHAR szPath[MAX_PATH]; 
	TCHAR szFileName[MAX_PATH]; 
	TCHAR* szAppName = "GameWorld";
	DWORD dwBufferSize = MAX_PATH;
	HANDLE hDumpFile;
	SYSTEMTIME stLocalTime;
	MINIDUMP_EXCEPTION_INFORMATION ExpParam;

	GetLocalTime( &stLocalTime );
	GetTempPath( dwBufferSize, szPath );

	StringCchPrintf( szFileName, MAX_PATH, "%s%s", szPath, szAppName );
	CreateDirectory( szFileName, NULL );

	StringCchPrintf( szFileName, MAX_PATH, "Data\\Online\\%04d%02d%02d-%02d%02d%02d-%ld-%ld.dmp", 
		stLocalTime.wYear, stLocalTime.wMonth, stLocalTime.wDay, 
		stLocalTime.wHour, stLocalTime.wMinute, stLocalTime.wSecond, 
		GetCurrentProcessId(), GetCurrentThreadId());
	hDumpFile = CreateFile(szFileName, GENERIC_READ|GENERIC_WRITE, 
		FILE_SHARE_WRITE|FILE_SHARE_READ, 0, CREATE_ALWAYS, 0, 0);

	ExpParam.ThreadId = GetCurrentThreadId();
	ExpParam.ExceptionPointers = pExceptionPointers;
	ExpParam.ClientPointers = TRUE;

	bMiniDumpSuccessful = MiniDumpWriteDump(GetCurrentProcess(), GetCurrentProcessId(), 
		hDumpFile, MiniDumpWithDataSegs, &ExpParam, NULL, NULL);

	return EXCEPTION_EXECUTE_HANDLER;
}

class Test : public BasicSerializable<SwitchedSerializable<int, SwitchedField<1,int>>, int, char>
{
public:

	ACCESSOR_1(1, Test);
};

void Init()
{
	System::Log::Create("GameWorldServer.log");
	Skyrim::Logic::Session::Init();

	Test test;

	std::cout << test.get<0>().get<0>() << std::endl;
	Framework::Network::Packet p;
	p << test;
	Framework::System::PrintBinary((unsigned char*)p.GetBuffer().data(), p.GetBuffer().size());
	Framework::System::Log::Flush();
	system("pause");
}

void NewInstance()
{
	Skyrim::TheGameWorld = new Skyrim::GameWorld;
}

void main()
{
	Init();
	__try
	{
		//NewInstance();
		//Skyrim::TheGameWorld->Setup();

		//Skyrim::TheGameWorld->Run();
	}
	__except(GenerateDump(GetExceptionInformation()))
	{

	}
}