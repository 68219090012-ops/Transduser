#include <Arduino.h>

const int led1Pin = 12;
const int led2Pin = 13;
const unsigned long blinkInterval = 500; // ระยะเวลาเปิด/ปิด 500 ms

void setup() {
  pinMode(led1Pin, OUTPUT);
  pinMode(led2Pin, OUTPUT);
}

void loop() {
  digitalWrite(led1Pin, HIGH); // เปิดไฟ LED1
  digitalWrite(led2Pin, HIGH); // เปิดไฟ LED2
  delay(blinkInterval);

  digitalWrite(led1Pin, LOW); // ปิดไฟ LED1
  digitalWrite(led2Pin, LOW); // ปิดไฟ LED2
  delay(blinkInterval);
}
