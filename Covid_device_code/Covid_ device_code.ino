//Humidifier code

//Llibreries necessàries
#include "DHT.h" //Llibreria per el sensor de temperatura i humitat
#include <ESP8266WiFi.h>  //Llibreria per utilitzar el Wifi de la ESP
#include <BlynkSimpleEsp8266.h> //Llibreria per poder sincronitzar la ESP amb el Blynk


char auth[] = "kFTr4fo1msEHuA59x6igdfMcN75Hm75d"; //Token del nostre Blynk
char ssid[] = "super3"; //Id internet
char pass[] = "Sahyunone7"; //Password internet

DHT dhtA(5, DHT22); //Creació de l'objecte per comunicar-te amb el sensor i definició del pin

//Setup
void setup() {
  Blynk.begin(auth, ssid, pass);  //Establim connexió
  dhtA.begin();  //Inicialitzem
  pinMode(12, OUTPUT);  //Definició del pint 12 com a sortida, pin on hi ha connectat el relé
                        //encarregat de obrir o tancar el circut dels generadors d'humitat.
}


//Loop
void loop() {
  Blynk.run();  //Inicialitzem el Blynk
  climateRoutine();   //Cridem funció per llegir temperatura i humitat
  if (dhtA.readHumidity() < 50){   //Si la lectura de la humitat està per sota del 50%
    digitalWrite(12,LOW);}  // Alimentem el relè, per tant, s'engeguen els humificadors
  if (dhtA.readHumidity() > 60){  //Si la humitat està per sobre del 60%
    digitalWrite(12,HIGH);}       //Deixem de excitar el relé i per tant, obrim el circuit
                                  //la qual cosa aturarà els generadors de boira
}

//Funció per llegir Tº i humitat
void climateRoutine() {
    byte h1 = dhtA.readHumidity();   //Lectura i emmegatzematge de l'humitat
    byte t1 = dhtA.readTemperature(); //Lectura i emmagatzematge de la Tº.
    Blynk.virtualWrite(V0, t1);  //Enviem al Blynk el valor de la Tº per mostrar-lo
    Blynk.virtualWrite(V1, h1);  //Enviem al Blynk el valor de l'humitat per mostrar-la
}
