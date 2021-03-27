//Humidifier code

#include "DHT.h"                              
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>


char auth[] = "kFTr4fo1msEHuA59x6igdfMcN75Hm75d";
char ssid[] = "super3";
char pass[] = "Sahyunone7";

DHT dhtA(5, DHT22);

void setup() {
  Blynk.begin(auth, ssid, pass);
  dhtA.begin();
  pinMode(12, OUTPUT);
}

void loop() {
  Blynk.run();
  climateRoutine();
  if (dhtA.readHumidity() < 50){
    digitalWrite(12,LOW);}
  if (dhtA.readHumidity() > 60){
    digitalWrite(12,HIGH);}
}
void climateRoutine() {
    byte h1 = dhtA.readHumidity();
    byte t1 = dhtA.readTemperature();
    Blynk.virtualWrite(V0, t1);
    Blynk.virtualWrite(V1, h1);
}
