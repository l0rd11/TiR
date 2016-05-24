

#include <ESP8266WiFi.h>
#include <WiFiClient.h> 

#include <Servo.h> 

//////////////////////
// WiFi Definitions //
//////////////////////
const char WiFiAPPSK[] = "SIECTESTOWA";
const char ssid[] = "HELLOWORLD";
int pos=90;
int vel=30;
int hig=30;
WiFiServer server(80);
Servo myservo,velocity,heigh;
WiFiClient client;

void setup() 
{
  myservo.attach(12);
  velocity.attach(14);
  heigh.attach(16);
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, WiFiAPPSK);
  server.begin();
}

void loop() 
{
  
  // Check if a client has connected
   
  if(!client){
     client = server.available();
  }
   
  if (!client) {
    return;
  }

  // Read the first line of the request
  String req = client.readStringUntil('\n');

  char  a =  req[req.length()-1];
  pos = int(a);
  char  v =  req[req.length()-2];
  vel = int(v);
  char  h =  req[req.length()-3];
  hig = int(h);
  
  if(pos>180||pos<0){
            pos=90;
          }
  myservo.write(180-pos);
  velocity.write(vel);
  heigh.write(hig);

  delay(1);

}



