//Humidifier code

#include "DHT.h"//Library for temperature and humidity sensor
#include <ESP8266WiFi.h>//Library to use the Wifi of the ESP
#include <BlynkSimpleEsp8266.h>//Library to be able to synchronize the ESP with the Blynk

char auth[] = "kFTr4fo1msEHuA59x6igdfMcN75Hm75d";//Token from our Blynk
char ssid[] = "GuillemMa";//Id WIFI
char pass[] = "Guillem2000";//Password WIFI

DHT dhtA(5, DHT22);//Creation of the object to communicate with the sensor and definition of the pin

void setup() {
  Blynk.begin(auth, ssid, pass);//We establish connection
  dhtA.begin();//We initialize the dhtA sensor
  pinMode(15, OUTPUT);//Definition of pin 12 as output
  pinMode(13, OUTPUT);//Definition of pin 13 as output
}
void loop() {
  Blynk.run();//Initialize Blynk
  climateRoutine();//Function to read temperature and humidity
  if (dhtA.readHumidity() < 50){//If the humidity reading is below 50%
    digitalWrite(15,HIGH);// The humidifiers are turned on
    delay(2000);
    digitalWrite(13,HIGH);}// The fans are turned on
  if (dhtA.readHumidity() > 60){
    digitalWrite(15 ,LOW);//The humidifiers are turned off
    digitalWrite(13,LOW);}//The fans are turned off
}
void climateRoutine() {
    byte h1 = dhtA.readHumidity();//Humidity lecture
    byte t1 = dhtA.readTemperature();//Ambient temperature lecture
    Blynk.virtualWrite(V0, t1);//The ambient temperautre is shown by blynk
    Blynk.virtualWrite(V1, h1);//The humidity is shown by blynk
}
