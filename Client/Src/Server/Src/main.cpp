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



void Init()
{
	System::Log::Create("GameWorldServer.log");
	Skyrim::Logic::Session::Init();

	PlayerGOMEntryReplication t, t2;
	Framework::Network::Packet p;
	t.SetName("test");
	t.SetMount(true);
	t.SetLevel(10);
	p << t;
	std::cout << t.GetName() << std::endl;

	Framework::System::PrintBinary((uint8_t*)p.GetBuffer().data(), p.GetBuffer().size());
	Framework::System::Log::Flush();

	p >> t2;
	std::cout << t2.GetName() << std::endl;
	std::cout << t2.GetMount() << std::endl;
	std::cout << t.impl.m0.impl.mFlag << std::endl;

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