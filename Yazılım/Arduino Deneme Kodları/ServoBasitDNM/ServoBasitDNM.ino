
#include <Servo.h>

Servo servo1;
Servo servo2;

void setup() {

  servo1.attach(8);
  //servo2.attach(11);
}

void loop() {

  servo1.write(90);
  //servo2.write(120);
  delay(10);
//
//  servo1.write(140);
//  delay(1000);
//  
//  servo1.write(90);
//  delay(1000);
//
//  servo1.write(50);
//  delay(1000);
}
