#include "Particle.h"

#include "Adafruit_GFX_RK.h"
#include "Adafruit_LEDBackpack_RK.h"
#include "TCA9548A-RK.h"

SYSTEM_THREAD(ENABLED);


Adafruit_7segment sevenSeg;
Adafruit_AlphaNum4 alphaNum;

// Note: Because the default address for the TCA9548A is 0x70, which is also the address of the 
// LED backpack, we need to change the address. Connect the TCA9548A A0 line 1 to avoid the conflict!
TCA9548A mux(Wire, 1);


unsigned long blinkCheck = 0;
bool blinkState = false;
int counter1 = 0;
int counter2 = 0;

void setup() {
	Serial.begin(9600);

	mux.begin();

	mux.setChannel(0);
	sevenSeg.begin(0x70);
	
	mux.setChannel(1);
	alphaNum.begin(0x70);
	
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
	    
		// Use 7-segment display on channel 0
		mux.setChannel(0);
		
		blinkState = !blinkState;
		sevenSeg.drawColon(blinkState);
	    
		// Time.isValid() requires system firmware 0.6.0 or later	
		if (Time.isValid()) {
			int hour = Time.hour();
			if (hour < 10) {
				sevenSeg.writeDigitRaw(0, 0); // blank
			}
			else {
				sevenSeg.writeDigitNum(0, hour / 10);				
			}
			sevenSeg.writeDigitNum(1, hour % 10);				

			int minute = Time.minute();

			sevenSeg.writeDigitNum(3, minute / 10);				
			sevenSeg.writeDigitNum(4, minute % 10);				
		}
	    sevenSeg.writeDisplay();
	    
	    
		// Use alpha numeric display on channel 1
		mux.setChannel(1);

		alphaNum.writeDigitAscii(0, 'A' + (counter1++ % 26));
		
		alphaNum.writeDigitAscii(1, '0' + ((counter2 / 100) % 10));
		alphaNum.writeDigitAscii(2, '0' + ((counter2 / 10) % 10));
		alphaNum.writeDigitAscii(3, '0' + (counter2 % 10));
		counter2++;
		
		
		alphaNum.writeDisplay();

	}
}


