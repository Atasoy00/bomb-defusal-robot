#include <Arduino.h>
#include "WiFi.h"

const char* ssid = "***";
const char* password = "***";
 
WiFiServer wifiServer(80);


int joy[4];
int buton[8];
int tusx,tusy;


 
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

}
 
void loop() {
 
  WiFiClient client = wifiServer.available();
  int data[14];
 
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

      }
 
      delay(10);
    }
 
    client.stop();
    Serial.println("Client disconnected");
 
  }
}