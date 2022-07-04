#include <Arduino.h>
#include "WiFi.h"
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <PPMReader.h>

const char* ssid = "***";
const char* password = "***";

//const char* ssid = "***";
//const char* password = "***";

IPAddress staticIP(192, 168, 1, 166);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);
IPAddress dns(192, 168, 1, 1);

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

//-----Kanal Tepe Değerleri-------Kanal Taban Değerleri-----
unsigned int ch1MAX = 2000; unsigned int ch1MIN = 1050; 
unsigned int ch2MAX = 2000; unsigned int ch2MIN = 1045; 
unsigned int ch3MAX = 1985; unsigned int ch3MIN = 1105; 
unsigned int ch4MAX = 2050; unsigned int ch4MIN = 950; 
unsigned int ch5MAX = 2050; unsigned int ch5MIN = 950; 
unsigned int ch6MAX = 2050; unsigned int ch6MIN = 950; 

//-----Servoya Yazılacak Degerler-----
int ch1SER  =275;
int ch2SER  =430;
int ch2SER1 =430;
int ch3SER  =180;
int ch3SER1 =180;
int ch4SER  =260;
int ch5SER  =110;
int ch6SER  =275;

char rcKumanda = 0;

void setup() {
 
  Serial.begin(115200);

  //ch3 ppm okuması
  unsigned int ch3RAW = ppm.latestValidChannelValue(3, 0);

  Serial.println();
  if(ch3RAW>0){Serial.println("RC Kumanda Aktif"); rcKumanda=1;}
  else{Serial.println("Wifi Kontrol Modu");rcKumanda=0;}
 
  if(!(rcKumanda)) //Wifi Kontrol Modu
  {

    delay(1000);

    if (WiFi.config(staticIP, gateway, subnet, dns, dns) == false) 
    {
      Serial.println("Configuration failed.");
    }

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
      delay(1000);
      Serial.println("Connecting to WiFi..");
    }

    Serial.println("Connected to the WiFi network");
    Serial.println(WiFi.localIP());

    wifiServer.begin();

  }

  pwm.begin();
  pwm.setOscillatorFrequency(27000000);
  pwm.setPWMFreq(SERVO_FREQ);  // Analog servos run at ~50 Hz updates
  delay(10);

  pinMode(26, OUTPUT);
  pinMode(25, OUTPUT);
  pinMode(33, OUTPUT);
  pinMode(32, OUTPUT);

}
 
void loop() {
 
  if(!(rcKumanda))
  {
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


          digitalWrite(26,IN3);
          digitalWrite(25,IN4);
          digitalWrite(33,IN1);
          digitalWrite(32,IN2);

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

  else
  {
    //ppm okumaları
    unsigned int ch1RAW = ppm.latestValidChannelValue(1, 0);
    unsigned int ch2RAW = ppm.latestValidChannelValue(2, 0);
    unsigned int ch3RAW = ppm.latestValidChannelValue(3, 0);
    unsigned int ch4RAW = ppm.latestValidChannelValue(4, 0);
    unsigned int ch5RAW = ppm.latestValidChannelValue(5, 0);
    unsigned int ch6RAW = ppm.latestValidChannelValue(6, 0);

    if (ch1RAW > ch1MIN && ch1RAW < ch1MAX){ ch1SER = map(ch1RAW, ch1MIN, ch1MAX, SERVOMIN, SERVOMAX);}
    else{if(ch1RAW < ch1MIN){ch1SER=SERVOMIN;}if(ch1RAW > ch1MIN){ch1SER=SERVOMAX;}}
    if (ch2RAW > ch2MIN && ch2RAW < ch2MAX){ ch2SER = map(ch2RAW, ch2MIN, ch2MAX, SERVOMIN, SERVOMAX);}
    else{if(ch2RAW < ch2MIN){ch2SER=SERVOMIN;}if(ch2RAW > ch2MIN){ch2SER=SERVOMAX;}}
    if (ch3RAW > ch3MIN && ch3RAW < ch3MAX){ ch3SER = map(ch3RAW, ch3MIN, ch3MAX, SERVOMIN, SERVOMAX);}
    else{if(ch3RAW < ch3MIN){ch3SER=SERVOMIN;}if(ch3RAW > ch3MIN){ch3SER=SERVOMAX;}} 
    if (ch4RAW > ch4MIN && ch4RAW < ch4MAX){ ch4SER = map(ch4RAW, ch4MIN, ch4MAX, SERVOMIN, SERVOMAX);}
    else{if(ch4RAW < ch4MIN){ch4SER=SERVOMIN;}if(ch4RAW > ch4MIN){ch4SER=SERVOMAX;}}
    if (ch5RAW > ch5MIN && ch5RAW < ch5MAX){ ch5SER = map(ch5RAW, ch5MIN, ch5MAX, SERVOMIN, SERVOMAX);}
    else{if(ch5RAW < ch5MIN){ch5SER=SERVOMIN;}if(ch5RAW > ch5MIN){ch5SER=SERVOMAX;}}
    if (ch6RAW > ch6MIN && ch6RAW < ch6MAX){ ch6SER = map(ch6RAW, ch6MIN, ch6MAX, SERVOMIN, SERVOMAX);}
    else{if(ch6RAW < ch6MIN){ch6SER=SERVOMIN;}if(ch6RAW > ch6MIN){ch6SER=SERVOMAX;}}


//--------------------------------------------------------------------------------------------------------------------------------------------------//

    if(ch6SER<(SERVOMAX/2)) //Sürüş Modu
    {

    byte IN1,IN2,IN3,IN4;

    ch1SER = map(ch1SER,SERVOMIN,SERVOMAX,0,180);
    ch2SER = map(ch2SER,SERVOMIN,SERVOMAX,0,180);

    if     ((ch1SER>45  && ch1SER<135) && (ch2SER>45  && ch2SER<135))   {IN1=0;IN2=0;  IN3=0;IN4=0;}//dur
    else if((ch1SER>45  && ch1SER<135) && (ch2SER>135 && ch2SER<200))   {IN1=1;IN2=0;  IN3=1;IN4=0;}//ileri
    else if((ch1SER>45  && ch1SER<135) && (ch2SER>-20 && ch2SER<45))    {IN1=0;IN2=1;  IN3=0;IN4=1;}//geri
    else if((ch1SER>-20 && ch1SER<45)  && (ch2SER>45  && ch2SER<135))   {IN1=1;IN2=0;  IN3=0;IN4=1;}//sağ
    else if((ch1SER>135 && ch1SER<200) && (ch2SER>45  && ch2SER<135))   {IN1=0;IN2=1;  IN3=1;IN4=0;}//sol
    else if((ch1SER>-20 && ch1SER<45)  && (ch2SER>135 && ch2SER<200))   {IN1=1;IN2=0;  IN3=0;IN4=0;}//sağ ileri
    else if((ch1SER>135 && ch1SER<200) && (ch2SER>135 && ch2SER<200))   {IN1=0;IN2=0;  IN3=1;IN4=0;}//sol ileri
    else if((ch1SER>-20 && ch1SER<45)  && (ch2SER>-20 && ch2SER<45))    {IN1=0;IN2=1;  IN3=0;IN4=0;}//sağ geri
    else if((ch1SER>135 && ch1SER<200) && (ch2SER>-20 && ch2SER<45))    {IN1=0;IN2=0;  IN3=0;IN4=1;}//sol geri
    else                                                                {IN1=0;IN2=0;  IN3=0;IN4=0;}//dur


    digitalWrite(26,IN3);
    digitalWrite(25,IN4);
    digitalWrite(33,IN1);
    digitalWrite(32,IN2);
    
    }

//--------------------------------------------------------------------------------------------------------------------------------------------------//

    else if(ch6SER>(SERVOMAX/2)) //Robot Kol Modu   
    {

        //Ters Kinematik Denklem

        x = map(ch3SER, 100,450, 70,176);
        y = map(ch2SER, 100,450, 70,176);

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

        pwm.setPWM(11, 0, ch1SER);
        pwm.setPWM(12, 0, ch2SER);
        pwm.setPWM(13, 0, ch3SER);
        pwm.setPWM(14, 0, ch4SER);
        pwm.setPWM(15, 0, ch5SER);
    }
    

//--------------------------------------------------------------------------------------------------------------------------------------------------//
 // /*
    Serial.print(ch1RAW); Serial.print('\t'); Serial.print(ch1SER); Serial.print('\t'); 
    Serial.print(ch2RAW); Serial.print('\t'); Serial.print(q1_deg); Serial.print('\t'); 
    Serial.print(ch3RAW); Serial.print('\t'); Serial.print(q2_deg); Serial.print('\t');  
    Serial.print(ch4RAW); Serial.print('\t'); Serial.print(ch4SER); Serial.print('\t'); 
    Serial.print(ch5RAW); Serial.print('\t'); Serial.print(ch5SER); Serial.print('\t'); 
    Serial.print(ch6RAW); Serial.print('\t'); Serial.print(ch6SER); Serial.println(); 
 // */
 /*
    Serial.print("(1000,2000)  foo3/bar1 = "); Serial.println(foo3/bar1);
    Serial.print("(1000,2000)  foo2/bar2 = "); Serial.println(foo2/bar2);
    Serial.print("(100,450)  ch2SER = "); Serial.println(ch2SER);
    Serial.print("(100,450)  ch3SER = "); Serial.println(ch2SER);
    Serial.print("(70,176)  x = "); Serial.println(x);
    Serial.print("(70,176)  y = "); Serial.println(y);
    Serial.print("(-90,90)  q1_deg = "); Serial.println(q1_deg);
    Serial.print("(0,180)  q2_deg = "); Serial.println(q2_deg);

 */
    delay(10);
  }
}