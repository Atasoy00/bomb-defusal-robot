#include <Arduino.h>
#include <analogWrite.h>

void setup() {

pinMode(12,OUTPUT);
pinMode(13,OUTPUT);
pinMode(14,OUTPUT);
pinMode(27,OUTPUT);

analogWriteResolution(26, 12);
analogWriteResolution(25, 12);

}

void loop() {


digitalWrite(12,HIGH);
digitalWrite(13,LOW);
digitalWrite(14,HIGH);
digitalWrite(27,LOW);


analogWrite(26,200);
analogWrite(25,200);

delay(50);

}

