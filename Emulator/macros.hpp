#pragma once

#define todo(MSG) printf("TODO: %s", MSG); \
	exit(255);

#define err(MSG, ...) do { \
    printf("Error: " MSG "\n", ##__VA_ARGS__); \
    exit(1); \
} while (0);