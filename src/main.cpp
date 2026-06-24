#include <Arduino.h>

const int flamePin = 2;     // ขา DO ของเซ็นเซอร์ KY-026
const int analogPin = A0;   // ขา AO ของเซ็นเซอร์ KY-026

void setup() {
  pinMode(flamePin, INPUT);
  Serial.begin(9600);
  Serial.println("Testing KY-026 Flame Sensor");
  Serial.println("----------------------------");
}

void loop() {
  int digitalValue = digitalRead(flamePin);
  int analogValue = analogRead(analogPin);

  Serial.print("Digital Value: ");
  Serial.print(digitalValue);
  Serial.print(" | Analog Value: ");
  Serial.println(analogValue);

  delay(500);
}
