#include <iostream>
#include <fstream>
#include <string>

#include <cstdint>

#include "macros.hpp"
#include "cpu.hpp"
#include "callbacks.hpp"

int main(int argc, char** argv) {
	if (argc < 2) {
		printf("Usage: vise.exe [file]\n");
		return 1;
	}

	char* file = argv[1];
	std::ifstream in(file, std::ios_base::binary);

	if (!in.is_open()) {
		err("Couldn't open file!")
	}

	// Get length of the input stream
	in.seekg(0, std::ios::end);
	size_t len = in.tellg();

	// Go back to the start of the file
	in.seekg(0, std::ios::beg);

	if (len == 0 || len % 4 != 0) {
		err("Incomplete file!")
	}
	
	// Allocate buffer
	uint8_t* buffer = (uint8_t*)malloc(len);
	in.read((char*)buffer, len);

#ifdef _DEBUG
	// Print each hex value with offset to ensure everything went correctly
	for (int i = 0; i < len; i++) {
		printf("0x%02X ; (off: 0x%02X)\n", buffer[i], i);
	}

	printf("---\n");
#endif

	in.close();

	// Create a CPU and pass the array
	cpu_t computer = cpu_t(buffer, len);
	init_cpu_callbacks(computer);

	computer.execute();
}