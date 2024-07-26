#pragma once
#include "cpu.hpp"

void init_cpu_callbacks(cpu_t& cpu);

#pragma region CPU Callbacks

void write_to_register(cpu_t* ref, uint8_t reg, uint16_t data);
void read_from_register(cpu_t* ref, uint8_t reg, uint16_t unused);

#pragma endregion