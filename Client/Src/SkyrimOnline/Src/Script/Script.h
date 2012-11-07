#pragma once

#define SCRIPT_CHECK_NORETURN(x) if(!GameWorld::Exists()) \
	return;\
	\
	auto state = TheGameWorld->GetCurrentGameState();\
	if(!state){\
		System::Log::Debug("Skyrim Online hasn't registered any state yet.");\
		return;\
	}\
	\
	if(state->GetId() != x){\
	System::Log::Debug("The current game state doesn't allow the use of this function.");\
	return;\
	}

#define SCRIPT_CHECK(x) if(!GameWorld::Exists()){ \
		System::Log::Debug("Skyrim Online has not been started yet.");\
		return 0;\
	}\
	auto state = TheGameWorld->GetCurrentGameState();\
	if(!state){\
		System::Log::Debug("Skyrim Online hasn't registered any state yet.");\
		return 0;\
	}\
	\
	if(state->GetId() != x){\
	System::Log::Debug("The current game state doesn't allow the use of this function.");\
	return 0;\
	}