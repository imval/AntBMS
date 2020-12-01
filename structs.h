#ifndef STRUCTS_H
#define STRUCTS_H

#include <stdint.h>
#include <Arduino.h>

struct BMSStruct {
	float
		voltages[BATTERY_CELL_COUNT],
		capacity,
		totalCapacity,
		remainingCapacity,
		totalCycleCapacity,
		current = 0.42;
	short
		temperatures[6];
	uint8_t
		percentage, 
		chargeFlag,
		dischargeFlag;
};

#endif
