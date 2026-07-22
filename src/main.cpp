/*
  ระบบตรวจจับเปลวไฟและเปิดพัดลมดูดควัน
  แสดงผลผ่าน Serial Monitor

  KY-026
  VCC -> 5V
  GND -> GND
  DO  -> D7

  Relay
  IN  -> D8
*/
#include <Arduino.h>
#define FLAME_PIN 7
#define RELAY_PIN 8

void setup() {

  pinMode(FLAME_PIN, INPUT);
  pinMode(RELAY_PIN, OUTPUT);

  digitalWrite(RELAY_PIN, LOW);

  Serial.begin(9600);

  Serial.println("=======================================");
  Serial.println("   Flame Detection System (KY-026)");
  Serial.println("=======================================");
  Serial.println("System Ready...");
  Serial.println();
}

void loop() {

  int flame = digitalRead(FLAME_PIN);

  Serial.println("-------------------------------");

  if (flame == LOW) {

    digitalWrite(RELAY_PIN, HIGH);

    Serial.println("Status      : WARNING!");
    Serial.println("Fire        : DETECTED");
    Serial.println("Relay       : ON");
    Serial.println("Exhaust Fan : ON");
  }
  else {

    digitalWrite(RELAY_PIN, LOW);

    Serial.println("Status      : NORMAL");
    Serial.println("Fire        : NOT DETECTED");
    Serial.println("Relay       : OFF");
    Serial.println("Exhaust Fan : OFF");
  }

  Serial.println("-------------------------------");
  Serial.println();

  delay(1000);
}