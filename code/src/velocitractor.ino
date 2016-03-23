#include <Servo.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>

//Wifi AP credentials
const char *ssid = "OmniBoard-Wifi-AP";
const char *password = "1234567890";

Servo servo1; 
String input;
boolean stringComplete = false;

WiFiServer server(80);

void setup(void)
{
  WiFi.mode(WIFI_AP); 
  WiFi.softAP(ssid, password);
  server.begin();
  Serial.begin(9600);
  //Pins configuration
  servo1.attach(D6);
  pinMode(D8, OUTPUT);
  pinMode(D7, OUTPUT);
}

void loop(void)
{
  WiFi.mode(WIFI_AP);

  WiFiClient client = server.available();
  if (!client) {
    delay(500);
    Serial.println(WiFi.localIP());
  }
  while (client.connected()) {
    while (client.available()) {
      input = client.readStringUntil('+');
      stringComplete = true;
    }
    if (stringComplete) {
      parseData(input);
      stringComplete = false;
    }
  }
}

void front() {
    servo1.write(90);
    analogWrite(D8, 1024);
    digitalWrite(D7, 1);
}

void back() {
    servo1.write(90);
    analogWrite(D8, 1024);
    digitalWrite(D7, 0);
}

void right() {
    servo1.write(135);
    analogWrite(D8, 1024);
    digitalWrite(D7, 1);
}

void left() {
    servo1.write(70);
    analogWrite(D8, 1024);
    digitalWrite(D7, 1);
}

void halt() {
    servo1.write(90);
    analogWrite(D8, 0);
}

void heart(){}
void flame(){}
void skull(){}
void plus(){}
void punch(){}
void mask(){}

void parseData(String data){
    Serial.println(data);
    int plusIndex = data.indexOf('+');

    if(data.substring(0,plusIndex).toInt()==1)
    front();
    else if(data.substring(0,plusIndex).toInt()==2)
    back();
    else if(data.substring(0,plusIndex).toInt()==3)
    left();
    else if(data.substring(0,plusIndex).toInt()==4)
    right();
    else if(data.substring(0,plusIndex).toInt()==5)
    halt();
    else if(data.substring(0,plusIndex).toInt()==6)
    heart();
    else if(data.substring(0,plusIndex).toInt()==7)
    flame();
    else if(data.substring(0,plusIndex).toInt()==8)
    skull();
    else if(data.substring(0,plusIndex).toInt()==9)
    plus();
    else if(data.substring(0,plusIndex).toInt()==10)
    punch();
    else if(data.substring(0,plusIndex).toInt()==11)
    mask();
}