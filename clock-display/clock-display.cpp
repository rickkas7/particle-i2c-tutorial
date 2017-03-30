#include "Particle.h"

#include "Adafruit_GFX_RK.h"
#include "Adafruit_LEDBackpack_RK.h"

SYSTEM_THREAD(ENABLED);

// This example requires Particle system firmware 0.6.1 or later

Adafruit_7segment matrix = Adafruit_7segment();

unsigned long blinkCheck = 0;
bool blinkState = false;

void setup() {
	Serial.begin(9600);
	matrix.begin(0x70);
	
	// Set timezone offset from UTC.
	// -4 = EDT, Eastern Daylight Time in the United States
	// -5 = EST or CDT
	// ...
	// -8 = PST
	Time.zone(-4);
}

void loop() {
	if (millis() - blinkCheck >= 500) {
		blinkCheck = millis();
	    
		blinkState = !blinkState;
		matrix.drawColon(blinkState);
	    
		// Time.isValid() requires system firmware 0.6.0 or later	
		if (Time.isValid()) {
			int hour = Time.hour();
			if (hour < 10) {
				matrix.writeDigitRaw(0, 0); // blank
			}
			else {
				matrix.writeDigitNum(0, hour / 10);				
			}
			matrix.writeDigitNum(1, hour % 10);				

			int minute = Time.minute();

			matrix.writeDigitNum(3, minute / 10);				
			matrix.writeDigitNum(4, minute % 10);				
		}
	    matrix.writeDisplay();
	}
}
