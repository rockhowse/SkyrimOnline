#pragma once

#include <windows.h>
#include <string>
#include <cstdint>
#include <vector>

typedef bool (*TCallOblivionFunction)(const char* fName, void* thisObj,std::vector<unsigned char>& parameterStack, double* result);
extern TCallOblivionFunction CallOblivionFunction;