/*
* Utilities class
*/

#ifndef _UTILS_H
#define _UTILS_H

#include <stdint.h>
#include "defines.h"
#include "structs.h"

namespace Utils{
	int16_t buffer_get_int16(const uint8_t *buffer, uint8_t index);

	int32_t buffer_get_int32(const uint8_t *buffer, uint8_t index);

	float buffer_get_float16(const uint8_t *buffer, uint8_t index, float scale = 1);

	float buffer_get_float32(const uint8_t *buffer, int32_t index, float scale = 1);
};

#endif
