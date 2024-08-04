#pragma once
#include <cstdint>
#include <functional>
#include <unordered_map>

#include "utils/num_utils.hpp"
#include "utils/flags.hpp"
#include "instruction.hpp"

#define CPU_CALLBACK std::function<void(cpu_t* ref, uint8_t add, uint16_t data)>

enum cpu_flag_t : uint8_t {
	overflow					= BIT(0),
	register_arithmetic			= BIT(1),
};
SETUP_ENUM_AS_FLAG(cpu_flag_t)

class cpu_t
{
public:
	cpu_t() = delete;
	cpu_t(uint8_t* instructions, int length);
	~cpu_t();

	void execute();
	void add_callback(uint8_t opcode, CPU_CALLBACK callback);
	uint16_t* get_register(const uint8_t& value);

	uint16_t reg_a;
	uint16_t reg_b;
	uint16_t reg_c;
	uint16_t reg_data;

	cpu_flag_t flags;

private:
	std::unordered_map<uint8_t, CPU_CALLBACK> m_Callbacks;
	std::list<instruction_t> m_Instructions;
};