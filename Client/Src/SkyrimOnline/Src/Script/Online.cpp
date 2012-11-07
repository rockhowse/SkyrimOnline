#include "stdafx.h"
#include "Online.h"
#include <GameWorld.h>

namespace Skyrim
{
	/*UInt32 GetVersion(StaticFunctionTag* v)
	{
		std::ostringstream os;
		os << "Executed Online.GetVersion() with args : ";
		System::Log::Debug(os.str());

		return 1;
	}

	UInt32 SendChat(StaticFunctionTag* v, BSFixedString pMessage)
	{
		std::ostringstream os;
		os << "Executed Online.SendChat(const char* pMessage) with args : " << pMessage.data;
		System::Log::Debug(os.str());

		SCRIPT_CHECK('inga')

		Logic::NetEngine::GetInstance().SendChatMessage(pMessage.data);

		return 1;
	}*/

	void RegisterOnlineScript()
	{
	/*
		if(!*g_skyrimVM) return;

		VMClassRegistry		* registry =	(*g_skyrimVM)->GetClassRegistry();

		registry->RegisterFunction(
			new NativeFunction1 <StaticFunctionTag, UInt32, BSFixedString> ("SendChat", "Online", Skyrim::SendChat, registry));
		System::Log::Debug("Registered Online.SendChat(const char* pMessage)...");

		registry->RegisterFunction(
			new NativeFunction0 <StaticFunctionTag, UInt32> ("GetVersion", "Online", Skyrim::GetVersion, registry));
		System::Log::Debug("Registered Online.GetVersion()...");*/
	}
}
