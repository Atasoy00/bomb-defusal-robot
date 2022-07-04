#include <Wire.h>
#include <PPMReader.h>
#include <Adafruit_PWMServoDriver.h>
#include <Arduino.h>
#include "WiFi.h"

const char* ssid = "***";
const char* password = "***";

//const char* ssid = "***";
//const char* password = "***";

WiFiServer wifiServer(80);

int joy[4];
int buton[8];
int tusx,tusy;

// Initialize a PPMReader on digital pin 3 with 6 expected channels.
byte interruptPin = 4;
byte channelAmount = 6;
PPMReader ppm(interruptPin, channelAmount);

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

#define SERVOMIN  100 // This is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  450 // This is the 'maximum' pulse length count (out of 4096)
#define SERVO_FREQ 50 // Analog servos run at ~50 Hz updates

uint8_t servonum = 0;

int x,y;
double pi = 3.1415926535; 
double q1,q2,q1_deg,q2_deg;
uint l1=76,l2=174; //76,174
double foo1,bar1,foo2,bar2,foo3;
int move;

//-----Servoya Yazılacak Degerler-----
int ch1SER=275;
int ch2SER=430;
int ch2SER1=430;
int ch3SER=180;
int ch3SER1=180;
int ch4SER=260;
int ch5SER=110;


void setup() {
 
  Serial.begin(115200);
 
  delay(1000);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
 
  Serial.println("Connected to the WiFi network");
  Serial.println(WiFi.localIP());
 
  wifiServer.begin();

  pwm.begin();
  pwm.setOscillatorFrequency(27000000);
  pwm.setPWMFreq(SERVO_FREQ);  // Analog servos run at ~50 Hz updates
  delay(10);

  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(14, OUTPUT);
  pinMode(27, OUTPUT);

}
 
void loop() {
 
  WiFiClient client = wifiServer.available();
  int data[14];

  // kontrol okuma işlemi
 
  if (client) {
    while (client.connected()) {
      while (client.available()>0) {

        for(int i=0;i<14;i++)
        {
          int c = client.read();
          data[i] = c-53;
        }

        joy[0] = data[0]; joy[1] = data[1]; joy[2] = data[2]; joy[3] = data[3];
        buton[0] = data[4]; buton[1] = data[5]; buton[2] = data[6];  buton[3] = data[7]; 
        buton[4] = data[8]; buton[5] = data[9]; buton[6] = data[10]; buton[7] = data[11];
        tusx=data[12]; tusy=data[13];
        
        // servo değer hesaplamaları ----------------------------------------------------------------------------------------------

        move=3;
        //kavrama
        if(buton[0]){/*75*/ ch5SER=284;}
        if(buton[1]){/*50*/ ch5SER=197;}
        if(buton[2]){/*0*/  ch5SER=SERVOMIN+10;}
        if(buton[3]){/*100*/ch5SER=SERVOMAX-80;}
        
        //bilek_servo
        if(buton[4]){/*sola_don*/ch4SER+=move;if(ch4SER>SERVOMAX){ch4SER=SERVOMAX;}}
        if(buton[5]){/*saga_don*/ch4SER-=move;if(ch4SER<SERVOMIN){ch4SER=SERVOMIN;}}       

        //doner_servo
        if(buton[6]){/*sola_don*/ch1SER+=move;if(ch1SER>SERVOMAX){ch1SER=SERVOMAX;}}
        if(buton[7]){/*saga_don*/ch1SER-=move;if(ch1SER<SERVOMIN){ch1SER=SERVOMIN;}}

        //yukseklik
        if     (tusy == 1){/*yukarı*/ch2SER1+=move;if(ch2SER1>SERVOMAX){ch2SER1=SERVOMAX;}}
        else if(tusy ==-1){/*asagı*/ ch2SER1-=move;if(ch2SER1<SERVOMIN){ch2SER1=SERVOMIN;}}

        //derinlik
        if     (joy[3] ==-1){/*ileri*/ch3SER1+=move;if(ch3SER1>SERVOMAX){ch3SER1=SERVOMAX;}}
        else if(joy[3] == 1){/*geri*/ ch3SER1-=move;if(ch3SER1<SERVOMIN){ch3SER1=SERVOMIN;}}


        //Serial.print("ch2SERBBB = "); Serial.println(ch2SER1);
        //Serial.print("ch3SERBBB = "); Serial.println(ch3SER1);

        // sürüş kontrol --------------------------------------------------------------------------------------------------------------
        byte IN1,IN2,IN3,IN4;

        if     ((joy[0]==0)  && (joy[1]==0))   {IN1=0;IN2=0;  IN3=0;IN4=0;}//dur
        else if((joy[0]==0)  && (joy[1]==-1))  {IN1=1;IN2=0;  IN3=1;IN4=0;}//ileri
        else if((joy[0]==0)  && (joy[1]==1))   {IN1=0;IN2=1;  IN3=0;IN4=1;}//geri
        else if((joy[0]==1)  && (joy[1]==0))   {IN1=1;IN2=0;  IN3=0;IN4=1;}//sağ
        else if((joy[0]==-1) && (joy[1]==0))   {IN1=0;IN2=1;  IN3=1;IN4=0;}//sol
        else if((joy[0]==1)  && (joy[1]==-1))  {IN1=1;IN2=0;  IN3=0;IN4=0;}//sağ ileri
        else if((joy[0]==-1) && (joy[1]==-1))  {IN1=0;IN2=0;  IN3=1;IN4=0;}//sol ileri
        else if((joy[0]==1)  && (joy[1]==1))   {IN1=0;IN2=1;  IN3=0;IN4=0;}//sağ geri
        else if((joy[0]==-1) && (joy[1]==1))   {IN1=0;IN2=0;  IN3=0;IN4=1;}//sol geri
        else                                   {IN1=0;IN2=0;  IN3=0;IN4=0;}//dur


        digitalWrite(13,IN3);
        digitalWrite(12,IN4);
        digitalWrite(14,IN1);
        digitalWrite(27,IN2);


        // robot kol kontrolü -------------------------------------------------------------------------------------------------------------


        //Ters Kinematik Denklem

        x = map(ch3SER1, SERVOMIN,SERVOMAX, 70,176);
        y = map(ch2SER1, SERVOMIN,SERVOMAX, 70,176);

        
        //Serial.print("x = "); Serial.println(x);
        //Serial.print("y = "); Serial.println(y);

        //foo1 = (pow(l1,2)+pow(l2,2)-pow(x,2)-pow(y,2)); //yöntem1
        foo3 = (0-pow(l1,2)-pow(l2,2)+pow(x,2)+pow(y,2)); //yöntem2
        bar1 = (2*l1*l2);

        //q2 = pi - acos(foo1/bar1);
        q2 = acos(foo3/bar1);

        foo2 = (l2*sin(q2));
        bar2 = (l1+l2*cos(q2));

        q1 = atan(x/(y+0.0001))-atan(foo2/bar2);

        q1_deg = q1*57.2957795;
        q2_deg = q2*57.2957795;

        q1_deg = map(q1_deg, -90,90, 0,180);

        if(q1_deg>140) q1_deg = q1_deg-180;

        if(q2_deg>165) q2_deg = 165;
     
        //Serial.print("q1 = "); Serial.println(q1_deg);
        //Serial.print("q2 = "); Serial.println(q2_deg);

        //q1_deg = 0;
        //q2_deg = 0;

        ch2SER = map(q1_deg, 0,180, SERVOMAX,SERVOMIN); //ters yapıldı
        ch3SER = map(q2_deg, 0,180, SERVOMAX,SERVOMIN); //ters yapıldı

        //Serial.print("ch2SER = "); Serial.println(ch2SER);
        //Serial.print("ch3SER = "); Serial.println(ch3SER);

///*
        Serial.print("ch1SER = "); Serial.print(ch1SER); Serial.print('\t');
        Serial.print("ch2SER = "); Serial.print(ch2SER); Serial.print('\t');
        Serial.print("ch3SER = "); Serial.print(ch3SER); Serial.print('\t');
        Serial.print("ch4SER = "); Serial.print(ch4SER); Serial.print('\t');
        Serial.print("ch5SER = "); Serial.print(ch5SER); Serial.println();
        Serial.println();
//*/

        pwm.setPWM(11, 0, ch1SER);
        pwm.setPWM(12, 0, ch2SER);
        pwm.setPWM(13, 0, ch3SER);
        pwm.setPWM(14, 0, ch4SER); //bilek
        pwm.setPWM(15, 0, ch5SER);

/*
        Serial.print(joy[0]);     
        Serial.print(joy[1]);     
        Serial.print(joy[2]);     
        Serial.print(joy[3]);     
        Serial.print(buton[0]);     
        Serial.print(buton[1]);   
        Serial.print(buton[2]);   
        Serial.print(buton[3]);   
        Serial.print(buton[4]);   
        Serial.print(buton[5]);   
        Serial.print(buton[6]);
        Serial.print(buton[7]);
        Serial.print(tusx);
        Serial.print(tusy);
        Serial.println();
*/

      }
 
      //delay(10);
    }
 
    client.stop();
    Serial.println("Client disconnected");
 
  }
}