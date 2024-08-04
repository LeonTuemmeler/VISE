#pragma once
#include <stdexcept>

#define todo(MSG) printf("TODO: %s", MSG); \
	exit(255);

#define err(MSG, ...) do { \
    printf("Error: " MSG "\n", ##__VA_ARGS__); \
    exit(1); \
} while (0);

#ifdef _DEBUG
#define DEBUG_SEPERATOR(MSG, ...) printf("\n-- " MSG " --\n\n", ##__VA_ARGS__);
#else
#define DEBUG_SEPERATOR(MSG, ...)
#endif