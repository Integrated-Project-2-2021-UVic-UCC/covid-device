//Covid device code

#define BLYNK_PRINT Serial


//Llibreries
#include <ESP8266WiFi.h>  //Llibreria ESP per connectar el Wifi
#include <BlynkSimpleEsp8266.h> //Llibreria per utilitzar les funcions de la ESP
#include <Wire.h>  //Llibreria pel sensor de Tº
#include <Adafruit_MLX90614.h>  //Llibreria pel sensor de Tº

char auth[] = "tbZIhFWo3vJvHYH9O96tM7k3MW_dZea6";   //Token Blynk
char ssid[] = "super3"; //SSID internet
char pass[] = "Sahyunone7"; //Password internet

Adafruit_MLX90614 mlx = Adafruit_MLX90614(); //Creació de la variable per interectuar amb el sensor
const int sensorInfraroig = 13; //Sensor infrarroig al pin 13
const int analog_ip = A0;   //Analog_ip al pin A0
int capacity = 0;   //capacitat al pin 0
const int sensorMax = 16; //sensor de nivell al màxim al pin 16
const int sensorMin = 15; //sensor de nivell mínim al 15
const int bomba = 14;   //Bomba reomplir al pin 14

//Setup
void setup() {
  Serial.begin(9600); //Serial port amb un baud rate de 9600
  Blynk.begin(auth, ssid, pass); //Connectem el token i l'internet
  mlx.begin();
  pinMode(sensorInfraroig , INPUT); //Declaració del sensor d'infrarroig com a input
  pinMode(sensorMax, INPUT_PULLUP); //Declaració del sensor de nivell màxim com a input
  pinMode(sensorMin, INPUT_PULLUP); //Declaració del sensor de nivell mínim com a input
  pinMode(bomba, OUTPUT); ////Declaració de la bomba com a OUTPUT
  digitalWrite(12, HIGH);  //Inicialment el dosificador està aturat
  digitalWrite(bomba, HIGH); //Inicialment la bomba està aturada
}
//Loop
void loop() {
  Blynk.run(); //Iniciem el blyink
  int detectTemp = 0; //Definició de la variable de detectar temperatura inicialment a 0
  int valor = 0;   //Definició del valor donat pel sensor de distància inicialment a 0
  detectTemp = digitalRead(sensorInfraroig); //Lectura i assignació del valor del sensor infrarroig
  valor = analogRead(analog_ip);  //Lectura i assignació del valor donat pel detector de distància
  if (digitalRead(sensorMax) == 0){ //Si es detecta que el nivell està al màxim
      digitalWrite(bomba, HIGH);}  //Aturada de la bomba
  if (digitalRead(sensorMin) == 1){  //Si es detecta que el nivell està al mínim
        digitalWrite(bomba, LOW);}   //Ativació de la bomba
  if (detectTemp == LOW) {    //Si es detecta temperatura
      byte tp = mlx.readObjectTempC(); //Lectura l'objecte temperatura
      Blynk.virtualWrite(V2, tp);  //Mostrar pel Blynk el valor de la temperatura
      digitalWrite(12,LOW);  //Activació el dosificador
      delay(1000); //Delay per dosificar gel
      digitalWrite(12,HIGH);  //Aturada del dosificador
      capacity = capacity+1;  //Increment d'una unitat el valor de la capacitat
      delay(3000);  //delay per esperar
      Blynk.virtualWrite(V2, 0);} //Escriptura de valor de Tº a zero

  if (valor < 400) {  //Si el valor de la distància està per sota 400(rang de detecció)
      capacity=capacity-1; //disminució una unitat la capacitat
      delay(1000);}  //Delay de 1 segons per deixar que la persona passi per la porta

  Blynk.virtualWrite(V7,capacity);  //Escriptura al Blynk el nombre de gent a l'interior
}
