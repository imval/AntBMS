#include "utils.h"

namespace Utils {
	int16_t buffer_get_int16(const uint8_t *buffer, uint8_t index) {
		return (((uint16_t)buffer[index]) << 8) + ((uint16_t)buffer[index + 1]);
	}

	int32_t buffer_get_int32(const uint8_t *buffer, uint8_t index) {
		return ((uint32_t)buffer[index]) << 24 |
			((uint32_t)buffer[index + 1]) << 16 |
			((uint32_t)buffer[index + 2]) << 8 |
			((uint32_t)buffer[index + 3]);
	}

	float buffer_get_float16(const uint8_t *buffer, uint8_t index, float scale) {
		return (float)buffer_get_int16(buffer, index) / scale;
	}

	float buffer_get_float32(const uint8_t *buffer, int32_t index, float scale) {
		return (float)buffer_get_int32(buffer, index) / scale;
	}

}

