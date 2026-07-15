#include <Arduino.h>

const int ledPin = 13; // ขา LED บนบอร์ด Arduino UNO
const unsigned long blinkInterval = 500; // ระยะเวลาเปิด/ปิด 500 ms

void setup() {
  pinMode(ledPin, OUTPUT);
}

void loop() {
  digitalWrite(ledPin, HIGH); // เปิดไฟ LED
  delay(blinkInterval);
  digitalWrite(ledPin, LOW); // ปิดไฟ LED
  delay(blinkInterval);
}