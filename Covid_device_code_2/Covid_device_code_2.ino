//Covid device code 2

const int bomba_2 = 12;//Pump 2 to pin 12
const int sensorMax = 16;//SensorMax level to pin 16
const int sensorMin = 14;//SensorMin level to pin 14

void setup() {
  pinMode(bomba_2, OUTPUT);//Declaration of pump 2 as output
  pinMode(sensorMax, INPUT);//SensorMax declaration as input
  pinMode(sensorMin, INPUT);//SensorMin declaration as input
  digitalWrite(bomba_2, LOW);}//Initialize pump 2 off

void loop() {
  if (digitalRead(sensorMax) == 0){//If detects sensorMax as a 0
      digitalWrite(bomba_2, LOW);}//Deactivate pump 2
  if (digitalRead(sensorMin) == 1){//If detects SensorMin as a 1
        digitalWrite(bomba_2, HIGH);}//Activate pump 2
}
