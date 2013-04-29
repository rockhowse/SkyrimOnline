// proxydll.cpp
#include "common/plugin.h"
#include "common/skyscript.h"
#include <string>

#pragma unmanaged

HINSTANCE           gl_hOriginalDll;
HINSTANCE           gl_hThisInstance;

TNativeCall NativeCall;						 
TObscriptCall ObscriptCall;				 
TGetPlayerObjectHandle GetPlayerObjectHandle; // same as Game::GetPlayer()
TGetConsoleSelectedRef GetConsoleSelectedRef; // gets the object ref selected in the console menu
Tdyn_cast dyn_cast;							 // object dynamic casting
TRegisterPlugin RegisterPlugin;				 
TWait Wait;									 
TBSString_Create BSString_Create;			 
TBSString_Free BSString_Free;	
TExecuteConsoleCommand ExecuteConsoleCommand;  // executes command just like you typed in in the console
											   // 2nd param is parent handle which can be 0 or point to a ref
DWORD ___stack[MAX_STACK_LEN];
DWORD ___stackindex;
DWORD ___result;

HMODULE g_hModule;

void Error(char *pattern, ...)
{
	char text[1024];
	va_list lst;
	va_start(lst, pattern);
	vsprintf_s(text, pattern, lst);
	va_end(lst);
	MessageBoxA(0, text, "Online Mod plugin critical error", MB_ICONERROR); 
	ExitProcess(0);
}

std::string GetPathFromFilename(std::string filename)
{
	return filename.substr(0, filename.rfind("\\") + 1);
}

int IniReadInt(char *inifile, char *section, char *param, int def)
{
	char curdir[MAX_PATH];
	GetModuleFileNameA(g_hModule, curdir, sizeof(curdir));
	std::string fname = GetPathFromFilename(curdir) + inifile;
	return GetPrivateProfileIntA(section, param, def, fname.c_str());
}

bool GetKeyPressed(BYTE key)
{
  return (GetKeyState(key) & 0x80000000) > 0;
}

void PrintDebug(char *pattern, ...)
{
	char text[1024];
	va_list lst;
	va_start(lst, pattern);
	vsprintf_s(text, pattern, lst);
	va_end(lst);
	OutputDebugStringA(text);
}

void PrintNote(char *pattern, ...)
{
	char text[1024];
	va_list lst;
	va_start(lst, pattern);
	vsprintf_s(text, pattern, lst);
	va_end(lst);
	OutputDebugStringA(text);
	::Debug::Notification(text);
}

/*
	DO NOT CHANGE ANYTHING BELOW FOR ANY MEANS
*/

#define SCRIPT_DRAGON "ScriptDragon.dll" 

void SkyrimPluginInit(HMODULE hModule)
{
	HMODULE hDragon = LoadLibraryA(SCRIPT_DRAGON);
	/* 
	In order to provide NORMAL support i need a plugins to be distributed without the DragonScript.dll engine 
	cuz user always must have the latest version which cud be found ONLY on my web page
	*/
	if (!hDragon) Error("Can't load %s, download latest version from http://alexander.sannybuilder.com/Files/tes/", SCRIPT_DRAGON);
	NativeCall = (TNativeCall)GetProcAddress(hDragon, "Nativecall");
	ObscriptCall = (TObscriptCall)GetProcAddress(hDragon, "Obscriptcall");
	GetPlayerObjectHandle = (TGetPlayerObjectHandle)GetProcAddress(hDragon, "GetPlayerObjectHandle");
	ExecuteConsoleCommand = (TExecuteConsoleCommand)GetProcAddress(hDragon, "ExecuteConsoleCommand");
	GetConsoleSelectedRef = (TGetConsoleSelectedRef)GetProcAddress(hDragon, "GetConsoleSelectedRef");
	dyn_cast = (Tdyn_cast)GetProcAddress(hDragon, "dyn_cast");
	RegisterPlugin = (TRegisterPlugin)GetProcAddress(hDragon, "RegisterPlugin");
	Wait = (TWait)GetProcAddress(hDragon, "WaitMs");
	BSString_Create = (TBSString_Create)GetProcAddress(hDragon, "BSString_Create");
	BSString_Free = (TBSString_Free)GetProcAddress(hDragon, "BSString_Free");

	if(!NativeCall || !ObscriptCall || !GetPlayerObjectHandle || !ExecuteConsoleCommand 
		|| !GetConsoleSelectedRef || !dyn_cast || !RegisterPlugin || !Wait
		|| !BSString_Create || !BSString_Free)
	{
		Error("ScriptDragon engine dll `%s` has not all needed functions inside, exiting", SCRIPT_DRAGON);
	}

	RegisterPlugin(hModule);
}

////////////////////////////////////////////////////////////////////////// Oblivion

TCallOblivionFunction CallOblivionFunction;

void OblivionPluginInit(HMODULE hModule)
{
	HMODULE hOblivion = GetModuleHandleA("Oblivion.Online.dll");
	CallOblivionFunction = (TCallOblivionFunction)GetProcAddress(hOblivion, "CallFunction");

	if(!CallOblivionFunction)
	{
		Error("Can't load the function !");
	}
}

#pragma unmanaged

extern "C" __declspec(dllexport) void main()
{
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD fdwReason, LPVOID lpReserved)
{
	switch (fdwReason)
	{
	case DLL_PROCESS_ATTACH:
		{
			std::string strL;
			strL.resize(MAX_PATH);
			GetModuleFileNameA(NULL, &strL[0], MAX_PATH) ;

			DisableThreadLibraryCalls((HMODULE)hModule);

			g_hModule = hModule;

			if(strL.find("TESV.exe") != std::string::npos)
			{
				SkyrimPluginInit(hModule);
			}
			else if(strL.find("Oblivion.exe") != std::string::npos)
			{
				OblivionPluginInit(hModule);
			}

			break;
		}
	case DLL_PROCESS_DETACH:
		{		
			break;
		}
	}
	return TRUE;
}