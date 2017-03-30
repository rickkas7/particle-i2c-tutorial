#include "Particle.h"
#include "Adafruit_BME280_RK.h"
#include "Ubidots.h"

#include <math.h> // isnan()

#define TOKEN "PASTE_YOUR_UBIDOTS_TOKEN_HERE"

Ubidots ubidots(TOKEN);

Adafruit_BME280 bme; // I2C

const unsigned long UPDATE_PERIOD_MS = 30000;

bool sensorReady = false;
unsigned long lastUpdate = 5000 - UPDATE_PERIOD_MS;
char buf[64];

void setup() {
	Serial.begin(9600);
	sensorReady = bme.begin();


}

void loop() {
	if (millis() - lastUpdate >= UPDATE_PERIOD_MS && sensorReady) {
		lastUpdate = millis();

		float temp = bme.readTemperature(); // degrees C
		// float pressure = bme.readPressure() / 100.0; // hPa
		float humidity = bme.readHumidity(); // %

		if (!isnan(temp) && !isnan(humidity)) {
			ubidots.add("temperature", temp);
			ubidots.add("humidity", humidity);
			ubidots.sendAll();

			Serial.printlnf("send temperature=%.1f humidity=%.1f", temp, humidity);
		}
	}
}
