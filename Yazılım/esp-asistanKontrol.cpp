#include <PPMReader.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>


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
    delay(10);

    pinMode(13, OUTPUT);
    pinMode(12, OUTPUT);
    pinMode(14, OUTPUT);
    pinMode(27, OUTPUT);

}

void loop() {

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


    digitalWrite(13,IN1);
    digitalWrite(12,IN2);
    digitalWrite(14,IN3);
    digitalWrite(27,IN4);
    
    }

//--------------------------------------------------------------------------------------------------------------------------------------------------//

    else if(ch6SER>(SERVOMAX/2)) //Robot Kol Modu
    {

        //Ters Kinematik Denklem

        x = map(ch3SER, 100,450, 0,250);
        y = map(ch2SER, 100,450, 0,250);

        foo1 = (pow(l1,2)+pow(l2,2)-pow(y,2)-pow(x,2)); //yöntem1
        foo3 = (0-pow(l1,2)-pow(l2,2)+pow(y,2)+pow(x,2)); //yöntem2
        bar1 = (2*l1*l2);

        //q2 = pi - acos(foo1/bar1);
        q2 = acos(foo3/bar1);

        foo2 = (l2*sin(q2));
        bar2 = (l1+l2*cos(q2));

        q1 = atan(x/(y+0.0001))-atan(foo2/bar2);

        q1_deg = q1*57.2957795;
        q2_deg = q2*57.2957795;

        q1_deg = map(q1_deg, -90,90, 0,180); 

        //Serial.print("q1 = "); Serial.println(q1_deg);
        //Serial.print("q2 = "); Serial.println(q2_deg);

        ch2SER = map(q1_deg, 0,180, SERVOMIN,SERVOMAX);
        ch3SER = map(q1_deg, 0,180, SERVOMIN,SERVOMAX);

        pwm.setPWM(11, 0, SERVOMAX-ch1SER);
        pwm.setPWM(12, 0, ch2SER);
        pwm.setPWM(13, 0, ch3SER);
        pwm.setPWM(14, 0, ch4SER);
        pwm.setPWM(15, 0, ch5SER);
    }

//--------------------------------------------------------------------------------------------------------------------------------------------------//


    Serial.print(ch1RAW); Serial.print('\t'); Serial.print(ch1SER); Serial.print('\t'); 
    Serial.print(ch2RAW); Serial.print('\t'); Serial.print(ch2SER); Serial.print('\t'); 
    Serial.print(ch3RAW); Serial.print('\t'); Serial.print(ch3SER); Serial.print('\t');  
    Serial.print(ch4RAW); Serial.print('\t'); Serial.print(ch4SER); Serial.print('\t'); 
    Serial.print(ch5RAW); Serial.print('\t'); Serial.print(ch5SER); Serial.print('\t'); 
    Serial.print(ch6RAW); Serial.print('\t'); Serial.print(ch6SER); Serial.println();
    delay(20);


}

