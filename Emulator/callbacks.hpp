#pragma once
#include "devices/cpu.hpp"

void init_cpu_callbacks(cpu_t& cpu);

#pragma region CPU Callbacks

void write_to_register(cpu_t* ref, uint8_t reg, uint16_t data);
void read_from_register(cpu_t* ref, uint8_t reg, uint16_t unused);
void copy_from_register(cpu_t* ref, uint8_t flag, uint16_t data);
void clear_register(cpu_t* ref, uint8_t reg, uint16_t unused);

void set_arithmetic_mode(cpu_t* ref, uint8_t toggle, uint16_t unused);

void cpu_add(cpu_t* ref, uint8_t destination, uint16_t value);
void cpu_sub(cpu_t* ref, uint8_t destination, uint16_t value);
void cpu_mul(cpu_t* ref, uint8_t destination, uint16_t value);
void cpu_div(cpu_t* ref, uint8_t destination, uint16_t value);
void cpu_mod(cpu_t* ref, uint8_t destination, uint16_t value);

#pragma endregion