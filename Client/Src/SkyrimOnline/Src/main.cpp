#include "stdafx.h"
#include <GameWorld.h>
#include <Script/Online.h>
#include <Logic/Session.h>


void ShowVersion()
{
	std::ostringstream os;
	os << "You need the game in 1.9.32.0 to play Skyrim Online. Hash dump : " << std::hex << *(DWORD *)(0x00DDDC00);
	::Debug::Notification((char*)os.str().c_str());
}

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

	::Debug::ShowMessageBox("Skyrim Online just crashed ! Please send the .dmp file in Data/Online on the crash forums.");

	return EXCEPTION_EXECUTE_HANDLER;
}

class IRunnable
{
public:
	virtual ~IRunnable(){};
	virtual void Update() = 0;
};

bool GetKeyPressed(BYTE key)
{
	return (GetKeyState(key) & 0x80000000) > 0;
}

class SkyrimOnlinePlugin : public IRunnable
{
public:

	SkyrimOnlinePlugin()
		:mElapsed(0)
	{
		System::Log::Create("GameWorldClient.log");
		Skyrim::Logic::Session::Init();
	}

	~SkyrimOnlinePlugin()
	{

	}

	void Init()
	{
		DragonPluginInit();
		FreeScript::ObjectReference::AddItem = ::ObjectReference::AddItem;

		switch ( *(DWORD *)(0x00DDDC00) ) 
		{
		case 0x468b0cc4 : // 1.9.32.0
			{
				break;
			}

		default :
			{
				MessageBox(0, "You must use version 1.9.32.0 to play Skyrim Online.", "Error", 0);
				return;
			}
		}

		std::ostringstream os;
		os << "Version : " << std::hex << *(DWORD *)(0x00DDDC00);
		System::Log::Debug(os.str());
		System::Log::Flush();

		if(!EasySteam::Interface::GetInstance() || !EasySteam::Interface::GetInstance()->GetUser()->IsLoggedOn())
		{
			::Debug::ShowMessageBox("Unable to retrieve steam.");
			return;
		}

		Skyrim::RegisterOnlineScript();

		srand((unsigned int)time(NULL));
		::Debug::Notification("To play Skyrim Online, press F3");

		Skyrim::TheGameWorld = new Skyrim::GameWorld;
		Skyrim::TheGameWorld->Setup();
	}

	void Update()
	{
		__try
		{
			if(FreeScript::Game::GetPlayer()->parentCell)
			{
				if(Skyrim::TheGameWorld)
				{
					Skyrim::TheGameWorld->Run();
				}
				else if(GetKeyPressed(VK_F3) && !Skyrim::TheGameWorld)
				{
					Init();
				}
				else
				{
					/*mElapsed = clock() - mElapsed;
					//if( > 10000)
					{
						Debug::Notification("To play Skyrim Online, press F3");
						System::Log::Debug("Debug");
						mElapsed = clock();
					}*/
				
				}
			}
			System::Log::Flush();
		}
		__except(GenerateDump(GetExceptionInformation()))
		{

		}
	}

private:

	uint32_t mElapsed;
};

extern "C"
{
	__declspec(dllexport) IRunnable* Initialize()
	{
		System::Log::Create("GameWorldClient.log");
		return new SkyrimOnlinePlugin;
	}
};
