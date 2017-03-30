#include "Particle.h"
#include "DS75-RK.h"

SYSTEM_MODE(MANUAL);

const unsigned long PRINT_PERIOD_MS = 5000;
unsigned long lastPrint = 0;

DS75 temp(Wire1, 0);

void setup() {
	Serial.begin(9600);
	temp.begin();
}

void loop() {
	if (millis() - lastPrint >= PRINT_PERIOD_MS) {
		lastPrint = millis();

		float tempC = temp.getTemperature();

		Serial.printlnf("temp %fC %fF", tempC, temp.convertCtoF(tempC));
	}
}

