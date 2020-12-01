/* Constants definition here */
#ifndef _DEFINES
#define _DEFINES

#include <stdint.h>
#include <Arduino.h>

#define DEBUG true
#define TIMEOUT 50

// Serial definitions
#define BMS_SERIAL   Serial2
#define DEBUG_SERIAL  Serial

#define BMS_INTERVAL_READ  500
#define BMS_DELAY_RESPONSE 200

#define BATTERY_CELL_COUNT 13

/*const String chargeFlags[] PROGMEM = {
	"Off",
	"Open",
	"Overvoltage Protection",
	"Over Current Protection",
	"Battery Full",
	"Total overvoltage",
	"Battery Over Temp",
	"PowerStage Over Temp",
	"Abnormal Current",
	"Balance line disconnected",
	"BMS Overtemp",
	"Discharge abnormal",
	"Manually OFF"
};

const String dischargeFlags[] PROGMEM = {
	"Off",
	"Open",
	"Over Discharge protection",
	"Over Current protection",
	"Something happened",
	"Total undervoltage"
	"Battery Over Temp",
	"PowerStage Over Temp",
	"Abnormal Current",
	"Balance line disconnected",
	"BMS Overtemp",
	"Charge On",
	"Short circuit protection",
	"Discharge abnormal",
	"Start exception",
	"Manually Off"
};*/

#endif
