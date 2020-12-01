/*
* AntBMS Communication class
*/

#ifndef _ANTBMS_H
#define _ANTBMS_H

#include <stdint.h>
#include <Arduino.h>
#include "defines.h"
#include "structs.h"

class AntBMS {

	int status;
	uint8_t buffer[140], bufferCursor = 0;
	/*float voltages[BATTERY_CELL_COUNT], capacity, totalCapacity, remainingCapacity, totalCycleCapacity, current;
	short temperatures[6];
	uint32_t bootTimeSeconds, lastData = 0;
	uint8_t percentage;*/
	unsigned long lastData = 0;
	bool successfulRead = false;

public:

	void begin();
	void request_data();
	bool read_data(BMSStruct *values);
	void dump_packet();
	bool process_packet(BMSStruct *values);
	void printSerial(BMSStruct *values);
	int getStatus();
	uint32_t getAgeData();
	bool isOk();

};

#endif
