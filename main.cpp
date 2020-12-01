// this is an example and will not work as is (probably).

#include "defines.h"
#include "structs.h"
#include "Utils.h"
#include "AntBMS.h"
#include <elapsedMillis.h>

AntBMS BMS;

struct SabStruct SabValues;
elapsedMillis sinceBMSRead, sinceBMSQuery;

void setup(){
  BMS.begin();
}

void loop(){
  // Handle BMS communication
	if (!status.waitingBMSResponse &&
		sinceBMSRead > BMS_INTERVAL_READ) {
		//Serial.println("Request BMS...");
		status.waitingBMSResponse = true;
		BMS.request_data();
		sinceBMSQuery = 0;
	}

	if (status.waitingBMSResponse && sinceBMSQuery > BMS_DELAY_RESPONSE) {
		if (BMS.read_data(&BMSValues)) {
			//Serial.println("BMS OK Read");
			//if (DEBUG) BMS.dump_packet();
			//if (DEBUG) BMS.printSerial(&BMSValues);
		}
		else {
			Serial.println("Failed Read BMS");
		}
		status.waitingBMSResponse = false;
		sinceBMSRead = 0;
	}
}
