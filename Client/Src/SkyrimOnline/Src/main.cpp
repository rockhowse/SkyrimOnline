#include "stdafx.h"
#include <SkyrimOnline.h>
#include <Script/Online.h>

int GenerateDump(EXCEPTION_POINTERS* pExceptionPointers)
{
	BOOL bMiniDumpSuccessful;
	TCHAR szPath[MAX_PATH]; 
	TCHAR szFileName[MAX_PATH]; 
	TCHAR* szAppName = "SkyrimOnline";
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

	Debug::ShowMessageBox("Skyrim Online just crashed ! Please send the .dmp file in Data/Online on the crash forums.");

	return EXCEPTION_EXECUTE_HANDLER;
}


__declspec(dllexport) void main()
{
	__try
	{
		switch ( *(DWORD *)(0x00DDDC00) ) 
		{
		case 0x508B018B : // 1.7.7.0 ( 2012)
			{
				break;
			}

		default :
			{
				Debug::ShowMessageBox("You need the game in 1.7.7.0 to play SkyrimOnline.");
				return;
			}
		}

		if(!EasySteam::Interface::GetInstance().GetUser()->IsLoggedOn())
		{
			Debug::ShowMessageBox("Unable to retrieve steam.");
			return;
		}

		Skyrim::RegisterOnlineScript();

		srand((unsigned int)time(NULL));
		PrintNote("To play Skyrim Online, press F3");

		bool onlineMod = false;
		while(!Skyrim::SkyrimOnline::Exists())
		{
			if(GetKeyPressed(VK_F3))
			{
				onlineMod = true;
				Skyrim::SkyrimOnline::GetInstance().Setup();
				break;
			}
			Wait(0);
		}

		if(onlineMod || Skyrim::SkyrimOnline::Exists())
			Skyrim::SkyrimOnline::GetInstance().Run();
	}
	__except(GenerateDump(GetExceptionInformation()))
	{

	}
}