#include <Arduino.h>
#include <ESP32Servo.h>

Servo servo1;
int minUs = 550;
int maxUs = 2350;

// These are all GPIO pins on the ESP32
// Recommended pins include 2,4,12-19,21-23,25-27,32-33
// for the ESP32-S2 the GPIO pins are 1-21,26,33-42
int servo1Pin = 14;
int pos = 0;      // position in degrees
ESP32PWM pwm;

void setup()
{
  ESP32PWM::allocateTimer(0);
	servo1.setPeriodHertz(50);
}

void loop()
{
	servo1.attach(servo1Pin, minUs, maxUs);
	//pwm.attachPin(37, 10000);//10khz

  for (pos = 0; pos <= 180; pos += 5) { // sweep from 0 degrees to 180 degrees
		servo1.write(180);
		delay(40);             // waits 20ms for the servo to reach the position
	}
	for (pos = 180; pos >= 0; pos -= 5) { // sweep from 180 degrees to 0 degrees
		servo1.write(0);
		delay(40);
	}

  servo1.detach();

}




