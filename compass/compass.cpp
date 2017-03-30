#include "Particle.h"

#include "Adafruit_GFX_RK.h"
#include "Adafruit_LEDBackpack_RK.h"
#include "Adafruit_Sensor.h"
#include "Adafruit_LSM303_U.h"

SYSTEM_THREAD(ENABLED);

Adafruit_8x8matrix matrix = Adafruit_8x8matrix();

Adafruit_LSM303_Mag_Unified mag = Adafruit_LSM303_Mag_Unified(12345);

void checkCompass();

boolean magReady;
unsigned long checkTime = 0;


void setup() {
	Serial.begin(9600);
	matrix.begin(0x70);

	magReady = mag.begin();
}

void loop() {
	if (millis() - checkTime >= 500) {
		checkTime = millis();

		checkCompass();
	}
}


void checkCompass() {
	if (!magReady) {
		return;
	}
	
	sensors_event_t event; 
	mag.getEvent(&event);

	float headingRadians = atan2(event.magnetic.y, event.magnetic.x);
	
	float x = 5 * cos(headingRadians);
	float y = 5 * sin(headingRadians);
	
	matrix.clear();

	matrix.drawLine(3, 3, 3 + x, 3 + y, LED_ON);

	matrix.writeDisplay(); 	
}