#include "Particle.h"
#include "Adafruit_BME280_RK.h"
#include "Adafruit_GFX.h"
#include "Adafruit_SSD1306.h"

#include <math.h> // isnan()

Adafruit_BME280 bme; // I2C
Adafruit_SSD1306 display(-1);

const unsigned long UPDATE_PERIOD_MS = 2000;

bool sensorReady = false;
unsigned long lastUpdate = 0;
char buf[64];

void setup() {
	Serial.begin(9600);

	display.begin(SSD1306_SWITCHCAPVCC, 0x3C);

	sensorReady = bme.begin();
}


void loop() { 
	if (millis() - lastUpdate >= UPDATE_PERIOD_MS && sensorReady) {
		lastUpdate = millis();

		float temp = bme.readTemperature(); // degrees C
		//float pressure = bme.readPressure() / 100.0; // hPa
		float humidity = bme.readHumidity(); // % 

		display.clearDisplay();
		
		if (!isnan(temp) && !isnan(humidity)) {
			display.setTextSize(2);
			display.setTextColor(WHITE);
			display.setCursor(0,0);
			
			snprintf(buf, sizeof(buf), "%.1f C", temp);
			display.println(buf);

			snprintf(buf, sizeof(buf), "%.1f F", temp * 9.0 / 5.0 + 32.0);
			display.println(buf);

			snprintf(buf, sizeof(buf), "%.1f %% RH", humidity);
			display.println(buf);
		}
		display.display();
	}
}

