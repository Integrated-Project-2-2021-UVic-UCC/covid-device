//Humidifier code
#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = "tbZIhFWo3vJvHYH9O96tM7k3MW_dZea6";

char ssid[] = "GuillemMaza";
char pass[] = "Guillem2000";

void setup() {
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);

}

void loop() {
  Blynk.run();

}
