#include "callbacks.hpp"
#include "utils/macros.hpp"
#include "utils/num_utils.hpp"

void init_cpu_callbacks(cpu_t& cpu) {
	cpu.add_callback(0x00, write_to_register);
	cpu.add_callback(0x01, read_from_register);
	cpu.add_callback(0x02, copy_from_register);
	cpu.add_callback(0x03, clear_register);

	cpu.add_callback(0x10, set_arithmetic_mode);
	cpu.add_callback(0x11, cpu_add);
	cpu.add_callback(0x12, cpu_sub);
	cpu.add_callback(0x13, cpu_mul);
	cpu.add_callback(0x14, cpu_div);
	cpu.add_callback(0x15, cpu_mod);
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
		err("Failed to get register!")
	}

	ref->reg_data = *source;
}

void copy_from_register(cpu_t* ref, uint8_t flag, uint16_t data) {
	u16_halves_t halves = u16_to_halves(data);

	uint16_t* source = ref->get_register(halves.lower);
	uint16_t* destination = ref->get_register(halves.upper);

	if (source == nullptr || destination == nullptr) {
		err("Failed to get register!")
	}

	*destination = *source;

	if (flag) {
		*source = 0x0000;
	}
}

void clear_register(cpu_t* ref, uint8_t reg, uint16_t unused) {
	write_to_register(ref, reg, 0x0000);
}

/// <summary>
/// If the toggle is set to '0', the CPU will use the 16-bit input on an arithmatical function as a literal value,
/// if the toggle is set to anything else, the 16-bit input will be interpreted as a register
/// </summary>
/// <param name="ref"></param>
/// <param name="toggle"></param>
/// <param name="unused"></param>
void set_arithmetic_mode(cpu_t* ref, uint8_t toggle, uint16_t unused) {
	if (toggle == 0) {
		ref->flags &= ~cpu_flag_t::register_arithmetic;
		return;
	}

	ref->flags = ref->flags | cpu_flag_t::register_arithmetic;
}

uint16_t resolve_arithmetic_operand(cpu_t* ref, const uint16_t& value) {
	if (HAS_FLAG(ref->flags, cpu_flag_t::register_arithmetic)) {
		u16_halves_t halves = u16_to_halves(value);
		uint16_t* source_register = ref->get_register(halves.lower);

		if (source_register == nullptr)
			err("Failed to get source register!");

		return *source_register;
	}

	return value;
}

/* I don't want to modify 5 functions each time i want to make a small tweak
 * Love it or hate it, I'm doing this macro stuff
*/

#define CPU_ARITHMETIC(OPERATOR, COMPARE, CPU, DEST, VAL) \
	uint16_t* destination_reg = ref->get_register(DEST); \
	if (destination_reg == nullptr) \
		err("Failed to get destination register"); \
	uint16_t arithmetic_value = resolve_arithmetic_operand(CPU, VAL); \
	*destination_reg OPERATOR arithmetic_value; \
	if(*destination_reg COMPARE arithmetic_value) \
		ref->flags = ref->flags | cpu_flag_t::overflow;

void cpu_add(cpu_t* ref, uint8_t destination, uint16_t value) {
	CPU_ARITHMETIC(+=, <, ref, destination, value)
}

void cpu_sub(cpu_t* ref, uint8_t destination, uint16_t value) {
	CPU_ARITHMETIC(-=, >, ref, destination, value)
}

void cpu_mul(cpu_t* ref, uint8_t destination, uint16_t value) {
	CPU_ARITHMETIC(*=, <, ref, destination, value)
}

void cpu_div(cpu_t* ref, uint8_t destination, uint16_t value) {
	CPU_ARITHMETIC(/=, >, ref, destination, value)
}

void cpu_mod(cpu_t* ref, uint8_t destination, uint16_t value) {
	CPU_ARITHMETIC(%=, || false ||, ref, destination, value)
}