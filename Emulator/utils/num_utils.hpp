#pragma once
#include <cstdint>

#define BIT(x) 1 << x

#pragma pack(push, 1)
typedef struct {
	uint8_t lower;
	uint8_t upper;
} u16_halves_t;
#pragma pack(pop)

inline uint16_t halves_to_u16(const uint8_t& lower, const uint8_t& upper) {
	return ((uint16_t)lower << 8) | upper;
}

inline u16_halves_t u16_to_halves(const uint16_t& full) {
    u16_halves_t halves;
    halves.lower = full & 0xFF;        // Extract the lower 8 bits
    halves.upper = (full >> 8) & 0xFF; // Extract the upper 8 bits
    return halves;
}