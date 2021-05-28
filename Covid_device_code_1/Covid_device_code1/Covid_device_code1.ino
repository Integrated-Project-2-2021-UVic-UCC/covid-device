//Covid device code 1
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>//ESP library to connect the Wifi
#include <BlynkSimpleEsp8266.h>//Library to use the Blynk functions
#include <Wire.h>//Tº sensor library
#include <Adafruit_MLX90614.h>//Tº sensor library

char auth[] = "tbZIhFWo3vJvHYH9O96tM7k3MW_dZea6";//Token Blynk
char ssid[] = "GuillemMa";//SSID WIFI
char pass[] = "Guillem2000";//Password WIFI

Adafruit_MLX90614 mlx = Adafruit_MLX90614();//Creation of the variable to interectuate with the sensor
const int sensorInfraroig = 13;//nfraig sensor to pin 13
const int analog_ip = A0;//Analog_ip to pin A0
int capacity = 0;//Variable initial capacitatitzat to 0
const int bomba_1 = 12;//Gel dispenser to pin 12
const int LedVerd = 16;//LedVerd to pin 16
const int LedVermell = 14;//LedVermell to pin 14
const int Brunzidor = 15;//Brunzidor to pin 15

void setup() {
  Serial.begin(9600);//Serial port with a baud rate of 9600
  Blynk.begin(auth, ssid, pass);//Connect the token and the internet
  mlx.begin();
  pinMode(sensorInfraroig , INPUT);//Declaration of the infraig sensor with input
  pinMode(bomba_1, OUTPUT);//Dispenser statement com to OUTPUT
  pinMode(LedVerd, OUTPUT);//Statement from LedVerd com to OUTPUT
  pinMode(LedVermell, OUTPUT);//Statement from LedVermella com to OUTPUT
  pinMode(Brunzidor, OUTPUT);//Statement from Brunzidor com to OUTPUT
  digitalWrite(bomba_1, LOW);//Initialitzem the values ​​with a 0
  digitalWrite(LedVerd, LOW);
  digitalWrite(LedVermell, LOW);
  digitalWrite(Brunzidor, LOW);}
  
void loop() {
  Blynk.run();//Start blyink
  int detectHand = 0;//Defining the variable of detecting temperature initially at 0
  int valor = 0;//Defined the value of the distance sensor initially at 0
  detectTemp = digitalRead(sensorInfraroig);//Reading and assigning the infrared sensor value
  valor = analogRead(analog_ip);//Reading and assigning the value of the distance detector
  int tp = 0;//Variable of the person's temperature value
  if (detectHand == LOW) {//If detects your hand
      byte tp = mlx.readObjectTempC()+3.5;//Reading the object temperature summing a sensor reading error offset
      Blynk.virtualWrite(V2, tp);//Show with Blynk the temperature value
      digitalWrite(bomba_1,HIGH);//Gel dispenser activation
      delay(1000);// Wait a second
      digitalWrite(bomba_1,LOW);//Gel dispenser deactivation
      Blynk.virtualWrite(V2, 0);// Return to 0 the temperature value shown by Blynk
      if (tp > 37){// If the temperature is higher than 37º
        digitalWrite(LedVermell, HIGH);//The Red LED lights up
        digitalWrite(Brunzidor, HIGH);//The buzzer turns on
        delay(1000);}//For a second
      else {
        digitalWrite(LedVerd, HIGH);//The LedVerd lights up
        capacity = capacity+1;//The capacity increases
        delay(1000);}
      digitalWrite(LedVermell, LOW);//S'apaguen tots els dispositius
      digitalWrite(LedVerd, LOW);//The devices turn off
      digitalWrite(Brunzidor, LOW);
      delay(3000);}
  if (valor < 400) {//If detects a person leaving
      capacity=capacity-1;//The capacity decreases
      delay(2000);}
  Blynk.virtualWrite(V7,capacity);//The capacity is shown by blynk}
