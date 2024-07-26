#include "cpu.hpp"
#include "macros.hpp"

cpu_t::cpu_t(uint8_t* instructions, int length)
{
	// Parse array of uint8_t into array instruction_t
	if (length == 0 || length % 4 != 0) {
		err("CPU was given incomplete instructions")
	}

	m_Instructions = std::list<instruction_t>();

	int i = 0;
	do {
		uint8_t op_code			= instructions[i + 0];
		uint8_t additional		= instructions[i + 1];
		uint8_t data_0			= instructions[i + 2];
		uint8_t data_1			= instructions[i + 3];

		uint16_t full_data = ((uint16_t)data_0 << 8) | data_1;

#ifdef _DEBUG
		printf("0x%02X 0x%02X 0x%04X\n", op_code, additional, full_data);
#endif

		instruction_t instruction = { op_code, additional, full_data };
		m_Instructions.push_back(instruction);

		i += 4;
	} while (i < length);
}

cpu_t::~cpu_t() {
	m_Instructions.clear();
	m_Callbacks.clear();
}

void cpu_t::add_callback(uint8_t opcode, CPU_CALLBACK callback) {
	m_Callbacks.emplace(opcode, callback);
}

uint16_t* cpu_t::get_register(const uint8_t& value) {
	switch (value) {
	case 0x00:
		return &reg_a;
	case 0x01:
		return &reg_b;
	case 0x02:
		return &reg_c;
	case 0xF0:
		return &reg_data;
	default:
		return nullptr;
	}
}

void cpu_t::execute() {
#ifdef _DEBUG
	printf("- RUNNING CPU -\n");
#endif
	for (auto instruction : m_Instructions) {
		CPU_CALLBACK callback = m_Callbacks[instruction.opcode];
		
		if (callback == NULL) {
			err("Failed to get callback for instruction 0x%02X", instruction.opcode)
		}

		callback(this, instruction.additional, instruction.data);
	
#ifdef _DEBUG
		printf("A: 0x%04X, B: 0x%04X, C: 0x%04X, DATA: 0x%04X\n", reg_a, reg_b, reg_c, reg_data);
#endif
	}
}