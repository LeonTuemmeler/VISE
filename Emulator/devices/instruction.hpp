#pragma once
#include <cstdint>

#pragma pack(push, 1)
typedef struct
{
	uint8_t opcode;
	uint8_t additional;
	uint16_t data;
} instruction_t;
#pragma pack(pop)