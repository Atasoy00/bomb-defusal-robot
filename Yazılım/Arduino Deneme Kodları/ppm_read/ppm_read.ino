#include <PPMReader.h>
#include <Servo.h>

// Initialize a PPMReader on digital pin 3 with 6 expected channels.
byte interruptPin = 3;
byte channelAmount = 6;
PPMReader ppm(interruptPin, channelAmount);

Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
Servo servo5;
Servo servo6;

//-----Kanal Tepe Değerleri-------Kanal Taban Değerleri-----
unsigned int ch1MAX = 2000; unsigned int ch1MIN = 1055; 
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

//    servo1.attach(8);
//    servo2.attach(9);
//    servo3.attach(10);
//    servo4.attach(11);
//    servo5.attach(12);
//    servo6.attach(13);

    pinMode(10, OUTPUT);
    pinMode(11, OUTPUT);
    pinMode(12, OUTPUT);
    pinMode(13, OUTPUT);

    servo1.attach(8);
    servo2.attach(9);

}

void loop() {

    unsigned int ch1RAW = ppm.latestValidChannelValue(1, 0);
    unsigned int ch2RAW = ppm.latestValidChannelValue(2, 0);
    unsigned int ch3RAW = ppm.latestValidChannelValue(3, 0);
    unsigned int ch4RAW = ppm.latestValidChannelValue(4, 0);
    unsigned int ch5RAW = ppm.latestValidChannelValue(5, 0);
    unsigned int ch6RAW = ppm.latestValidChannelValue(6, 0);


    if (ch1RAW > ch1MIN && ch1RAW < ch1MAX){ ch1SER = map(ch1RAW, ch1MIN, ch1MAX, 0, 180);}
    else{if(ch1RAW < ch1MIN){ch1SER=0;}if(ch1RAW > ch1MIN){ch1SER=180;}}
    if (ch2RAW > ch2MIN && ch2RAW < ch2MAX){ ch2SER = map(ch2RAW, ch2MIN, ch2MAX, 0, 180);}
    else{if(ch2RAW < ch2MIN){ch2SER=0;}if(ch2RAW > ch2MIN){ch2SER=180;}}
    if (ch3RAW > ch3MIN && ch3RAW < ch3MAX){ ch3SER = map(ch3RAW, ch3MIN, ch3MAX, 0, 180);}
    else{if(ch3RAW < ch3MIN){ch3SER=0;}if(ch3RAW > ch3MIN){ch3SER=180;}} 
    if (ch4RAW > ch4MIN && ch4RAW < ch4MAX){ ch4SER = map(ch4RAW, ch4MIN, ch4MAX, 0, 180);}
    else{if(ch4RAW < ch4MIN){ch4SER=0;}if(ch4RAW > ch4MIN){ch4SER=180;}}
    if (ch5RAW > ch5MIN && ch5RAW < ch5MAX){ ch5SER = map(ch5RAW, ch5MIN, ch5MAX, 0, 180);}
    else{if(ch5RAW < ch5MIN){ch5SER=0;}if(ch5RAW > ch5MIN){ch5SER=180;}}
    if (ch6RAW > ch6MIN && ch6RAW < ch6MAX){ ch6SER = map(ch6RAW, ch6MIN, ch6MAX, 0, 180);}
    else{if(ch6RAW < ch6MIN){ch6SER=0;}if(ch6RAW > ch6MIN){ch6SER=180;}}

//    servo1.write(ch1SER);
//    servo2.write(ch2SER);
//    servo3.write(ch3SER);
//    servo4.write(ch4SER);
//    servo5.write(ch5SER);
//    servo6.write(ch6SER);

    byte IN1,IN2,IN3,IN4,ENA,ENB;

    if     ((ch1SER>45  && ch1SER<135) && (ch2SER>45  && ch2SER<135))   {IN1=0;IN2=0;ENA=0;    IN3=0;IN4=0;ENB=0;  }//dur
    else if((ch1SER>45  && ch1SER<135) && (ch2SER>135 && ch2SER<200))   {IN1=1;IN2=0;ENA=180;  IN3=1;IN4=0;ENB=180;}//ileri
    else if((ch1SER>45  && ch1SER<135) && (ch2SER>-20 && ch2SER<45))    {IN1=0;IN2=1;ENA=180;  IN3=0;IN4=1;ENB=180;}//geri
    else if((ch1SER>-20 && ch1SER<45)  && (ch2SER>45  && ch2SER<135))   {IN1=1;IN2=0;ENA=180;  IN3=0;IN4=1;ENB=180;}//sağ
    else if((ch1SER>135 && ch1SER<200) && (ch2SER>45  && ch2SER<135))   {IN1=0;IN2=1;ENA=180;  IN3=1;IN4=0;ENB=180;}//sol
    else if((ch1SER>-20 && ch1SER<45)  && (ch2SER>135 && ch2SER<200))   {IN1=1;IN2=0;ENA=180;  IN3=0;IN4=0;ENB=0;  }//sağ ileri
    else if((ch1SER>135 && ch1SER<200) && (ch2SER>135 && ch2SER<200))   {IN1=0;IN2=0;ENA=0;    IN3=1;IN4=0;ENB=180;}//sol ileri
    else if((ch1SER>-20 && ch1SER<45)  && (ch2SER>-20 && ch2SER<45))    {IN1=0;IN2=1;ENA=180;  IN3=0;IN4=0;ENB=0;  }//sağ geri
    else if((ch1SER>135 && ch1SER<200) && (ch2SER>-20 && ch2SER<45))    {IN1=0;IN2=0;ENA=0;    IN3=0;IN4=1;ENB=180;}//sol geri
    else                                                                {IN1=0;IN2=0;ENA=0;    IN3=0;IN4=0;ENB=0;  }//dur


    digitalWrite(10,IN1);
    digitalWrite(11,IN2);
    digitalWrite(12,IN3);
    digitalWrite(13,IN4);

    servo1.write(ENA);
    servo2.write(ENB);
    


    Serial.print(ch1RAW); Serial.print('\t'); Serial.print(IN1); Serial.print('\t'); 
    Serial.print(ch2RAW); Serial.print('\t'); Serial.print(IN2); Serial.print('\t'); 
    Serial.print(ch3RAW); Serial.print('\t'); Serial.print(IN3); Serial.print('\t');  
    Serial.print(ch4RAW); Serial.print('\t'); Serial.print(IN4); Serial.print('\t'); 
    Serial.print(ch5RAW); Serial.print('\t'); Serial.print(ENA); Serial.print('\t'); 
    Serial.print(ch6RAW); Serial.print('\t'); Serial.print(ENB); Serial.println();
    delay(20);
}
