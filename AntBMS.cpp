/*
AntBMS communication class
*/

#define SERIAL_TX_BUFFER_SIZE 256
#define SERIAL_RX_BUFFER_SIZE 256
/* REMEMBER TO SET THE BUFFER SIZE IN HardwareSerial.h !!! */

#include <stdint.h>
#include <Arduino.h>
#include "AntBMS.h"
#include "defines.h"
#include "Utils.h"

void AntBMS::begin() {
	BMS_SERIAL.begin(19200);
}

void AntBMS::request_data()
{
		//BMS_SERIAL.flush();
		while(BMS_SERIAL.available()) BMS_SERIAL.read();
		// request data for the controller
		BMS_SERIAL.write((byte)0x5a);
		BMS_SERIAL.write((byte)0x5a);
		BMS_SERIAL.write((byte)0x00);
		BMS_SERIAL.write((byte)0x00);
		BMS_SERIAL.write((byte)0x01);
		BMS_SERIAL.write((byte)0x01);
		BMS_SERIAL.flush();
}

bool AntBMS::read_data(BMSStruct *values) {
	int index = 0;
	const int message_size = 140;
	unsigned long start = millis();

	while (BMS_SERIAL.available() > 0) {
		buffer[index++] = BMS_SERIAL.read();

		// Check packet
		if (index == 140) {
			this->process_packet(values);
			// Packet read, exit the loop
			successfulRead = true;
			return true;
		}

		if (millis() - start > 200) {
			successfulRead = false;
			return false;
			Serial.println("BMS Timeout");
		}

	}
	Serial.println("BMS no data: " + (String)index + " chars read");
	//dump_packet();
	successfulRead = false;
	return false;
}

void AntBMS::dump_packet() {
	for (int i = 0; i < 140; i++) {
		if (i % 10 == 0) Serial.println();
		Serial.print(buffer[i], HEX); Serial.print(" ");
	}
}

bool AntBMS::process_packet(BMSStruct *values) {
	// Read cell voltages
	int cell = 0, i = 0;
	for (i = 6; i < (6 + BATTERY_CELL_COUNT * 2); i += 2) {
		values->voltages[cell] = Utils::buffer_get_float16(buffer, i, 1000);
		cell++;
	}

	// Read stuff
	values->current = Utils::buffer_get_float32(buffer, 70) / 10.0;
	values->percentage = (uint8_t)buffer[74];
	values->totalCapacity = Utils::buffer_get_int32(buffer, 75) / 1000000.0;
	values->remainingCapacity = Utils::buffer_get_int32(buffer, 79) / 1000000.0;
	values->totalCycleCapacity = Utils::buffer_get_int32(buffer, 83) / 1000.0;
	values->chargeFlag = (uint8_t)buffer[103];
	values->dischargeFlag = (uint8_t)buffer[104];

	// Temps
	int probe = 0;
	for (i = 91; i <= 102; i += 2) {
		values->temperatures[probe] = Utils::buffer_get_int16(buffer, i);
		probe++;
	}

	lastData = millis();

	return true;
}

void AntBMS::printSerial(BMSStruct *values)
{
	Serial.print("Current:"); Serial.println(values->current);
	Serial.print("Percentage:"); Serial.println(values->percentage);
	Serial.print("totalCapacity:"); Serial.println(values->totalCapacity);
	Serial.print("remainingCapacity:"); Serial.println(values->remainingCapacity);
	Serial.print("totalCapacity:"); Serial.println(values->totalCapacity);
	Serial.print("chargeFlag:"); Serial.println(values->chargeFlag);
	Serial.print("dischargeFlag:"); Serial.println(values->dischargeFlag);

	for (int probe = 0;probe < 6;probe++) {
		Serial.print("Probe " + (String)probe + ":"); Serial.println(values->temperatures[probe]);
	}

	for (int cell = 0; cell < BATTERY_CELL_COUNT; cell++) {
		Serial.print("Cell "); Serial.print(cell + 1); Serial.print(" : "); Serial.println(values->voltages[cell], 3);
	}
	Serial.print("\n\n");
}

int AntBMS::getStatus() {

}

uint32_t AntBMS::getAgeData() {
	return millis() - lastData;
}

bool AntBMS::isOk() {
	if (getAgeData() > 1000)
		return false;
	else
		return true;
}
