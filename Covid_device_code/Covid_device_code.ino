//Covid device code
#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = "kFTr4fo1msEHuA59x6igdfMcN75Hm75d";

char ssid[] = "YourNetworkName";
char pass[] = "YourPassword";

void setup() {
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);

}

void loop() {
  Blynk.run();

}
