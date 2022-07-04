#include <PPMReader.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include "WiFi.h"

const char* ssid = "***";
const char* password = "***";
 
WiFiServer wifiServer(80);

    unsigned int ch1RAW=1500;
    unsigned int ch2RAW=1500;
    unsigned int ch3RAW=1500;
    unsigned int ch4RAW=1500;
    unsigned int ch5RAW=1500;
    unsigned int ch6RAW=1500;
    unsigned int ch7RAW=1500;
    unsigned int ch8RAW=1500;
    unsigned int ch9RAW=1500;
    unsigned int ch0RAW=1500;


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

//-----Kanal Tepe Değerleri-------Kanal Taban Değerleri-----
unsigned int ch1MAX = 2000; unsigned int ch1MIN = 1050; 
unsigned int ch2MAX = 2000; unsigned int ch2MIN = 1045; 
unsigned int ch3MAX = 1985; unsigned int ch3MIN = 1105; 
unsigned int ch4MAX = 2050; unsigned int ch4MIN = 950; 
unsigned int ch5MAX = 2050; unsigned int ch5MIN = 950; 
unsigned int ch6MAX = 2050; unsigned int ch6MIN = 950; 

//-----Servoya Yazılacak Degerler-----
int ch1SER;
int ch2SER;
int ch3SER;
int ch4SER;
int ch5SER;
int ch6SER;


void setup() {

    Serial.begin(115200);

    pwm.begin();
    pwm.setOscillatorFrequency(27000000);
    pwm.setPWMFreq(SERVO_FREQ);  // Analog servos run at ~50 Hz updates
    delay(1000);

    WiFi.begin(ssid, password);
 
    while (WiFi.status() != WL_CONNECTED) 
    {
        delay(1000);
        Serial.println("Connecting to WiFi..");
    }
 
    Serial.println("Connected to the WiFi network");
    Serial.println(WiFi.localIP());
 
    wifiServer.begin();

    pinMode(13, OUTPUT);
    pinMode(12, OUTPUT);
    pinMode(14, OUTPUT);
    pinMode(27, OUTPUT);

}

void loop() {
/*
    //ppm okumaları
    unsigned int ch1RAW = ppm.latestValidChannelValue(1, 0);
    unsigned int ch2RAW = ppm.latestValidChannelValue(2, 0);
    unsigned int ch3RAW = ppm.latestValidChannelValue(3, 0);
    unsigned int ch4RAW = ppm.latestValidChannelValue(4, 0);
    unsigned int ch5RAW = ppm.latestValidChannelValue(5, 0);
    unsigned int ch6RAW = ppm.latestValidChannelValue(6, 0);
*/
    WiFiClient client = wifiServer.available();
    int data[40];
    
    if (client) 
    {
        while (client.connected()) 
        {
            while (client.available()>0) 
            {
                for(int i=0;i<40;i++)
                {
                    int c = client.read();
                    data[i] = c-48;
                }
        
                ch1RAW = 1000*data[0] +100*data[1] +10*data[2] +data[3]; 
                ch2RAW = 1000*data[4] +100*data[5] +10*data[6] +data[7]; 
                ch3RAW = 1000*data[8] +100*data[9] +10*data[10]+data[11]; 
                ch4RAW = 1000*data[12]+100*data[13]+10*data[14]+data[15]; 
                ch5RAW = 1000*data[16]+100*data[17]+10*data[18]+data[19]; 
                ch6RAW = 1000*data[20]+100*data[21]+10*data[22]+data[23]; 
                ch7RAW = 1000*data[24]+100*data[25]+10*data[26]+data[27]; 
                ch8RAW = 1000*data[28]+100*data[29]+10*data[30]+data[31]; 
                ch9RAW = 1000*data[32]+100*data[33]+10*data[34]+data[35]; 
                ch0RAW = 1000*data[36]+100*data[37]+10*data[38]+data[39]; 
                
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


                digitalWrite(13,IN1);
                digitalWrite(12,IN2);
                digitalWrite(14,IN3);
                digitalWrite(27,IN4);
                
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

                    pwm.setPWM(11, 0, SERVOMAX-ch1SER);
                    pwm.setPWM(12, 0, ch2SER);
                    pwm.setPWM(13, 0, ch3SER);
                    pwm.setPWM(14, 0, ch4SER);
                    pwm.setPWM(15, 0, ch5SER);
                }
                

            //--------------------------------------------------------------------------------------------------------------------------------------------------//
            }
            delay(10);
        }
 
    client.stop();
    Serial.println("Client disconnected");
 
  }

}

