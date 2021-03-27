//Covid device code

#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Wire.h>
#include <Adafruit_MLX90614.h>

char auth[] = "tbZIhFWo3vJvHYH9O96tM7k3MW_dZea6";
char ssid[] = "super3";
char pass[] = "Sahyunone7";

Adafruit_MLX90614 mlx = Adafruit_MLX90614();
const int sensorInfraroig = 13;
const int analog_ip = A0;
int capacity = 0;

void setup() {
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  mlx.begin();
  pinMode(sensorInfraroig , INPUT);
}

void loop() {
  Blynk.run();
  int detectTemp = 0;
  int valor = 0;
  detectTemp = digitalRead(sensorInfraroig);
  valor = analogRead(analog_ip);
  if (detectTemp == LOW) {
      byte tp = mlx.readObjectTempC();
      Blynk.virtualWrite(V2, tp);
      digitalWrite(2,LOW);
      delay(1000);
      digitalWrite(2,HIGH);
      capacity = capacity+1;
      delay(3000);
      Blynk.virtualWrite(V2, 0);}
  if (valor < 400) {
      capacity=capacity-1;
      delay(1000);}
  Blynk.virtualWrite(V7,capacity);
  delay(500);
}
