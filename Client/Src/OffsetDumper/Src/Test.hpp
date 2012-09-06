#pragma once

extern std::ofstream out;

#define OUTPUT out

void RunActorDump();
#define RUN_TEST(...) OUTPUT << std::hex << #__VA_ARGS__ << " : " << __VA_ARGS__ << std::endl;

using namespace FreeScript;