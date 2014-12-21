#pragma once

#include <cstdint>

void* FormAllocate(uint32_t size);
void FormFree(void* ptr);