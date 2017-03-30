#include "Particle.h"
#include "Adafruit_BME280_RK.h"

Adafruit_BME280 bme; // I2C

const unsigned long PUBLISH_PERIOD_MS = 60000;
const char *FIELD_SEPARATOR = "|||";
const char *EVENT_NAME = "tempSensor";

bool sensorReady = false;
unsigned long lastPublish = 0;
char buf[256];

void setup() {
    Serial.begin(9600);

    sensorReady = bme.begin();
}


void loop() { 
	if (millis() - lastPublish >= PUBLISH_PERIOD_MS && sensorReady) {
		lastPublish = millis();
		
		float temp = bme.readTemperature(); // degrees C
		float pressure = bme.readPressure() / 100.0; // hPa
		float humidity = bme.readHumidity(); // % 
		
		snprintf(buf, sizeof(buf), "%.02f%s%.02f%s%.01f", temp, FIELD_SEPARATOR, pressure, FIELD_SEPARATOR, humidity);
		Particle.publish(EVENT_NAME, buf, PRIVATE);
	}
}

