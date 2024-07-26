#include "callbacks.hpp"
#include "macros.hpp"

void init_cpu_callbacks(cpu_t& cpu) {
	cpu.add_callback(0x00, write_to_register);
	cpu.add_callback(0x01, read_from_register);
}

void write_to_register(cpu_t* ref, uint8_t reg, uint16_t data) {
	uint16_t* destination = ref->get_register(reg);
	if (destination == nullptr) {
		err("Failed to get register!")
	}

	*destination = data;
}

void read_from_register(cpu_t* ref, uint8_t reg, uint16_t unused) {
	uint16_t* source = ref->get_register(reg);
	if (source == nullptr) {
		err("Failed to get register!");
	}

	ref->reg_data = *source;
}