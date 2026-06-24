#include <Arduino.h>

const int flamePin = 2;      // ขา DO ของเซ็นเซอร์ KY-026
const int analogPin = A0;    // ขา AO ของเซ็นเซอร์ KY-026
const int ledPin = 13;       // LED แสดงสถานะ
const int buzzerPin = 8;     // Buzzer สำหรับแจ้งเตือน

const int flameThreshold = 300;  // เกณฑ์ค่าที่ถือว่าเจอแสง/เปลวไฟ

void setup() {
  pinMode(flamePin, INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  Serial.begin(9600);
  Serial.println("โปรแกรมตรวจจับเปลวไฟ");
  Serial.println("------------------------");
}

void loop() {
  int digitalValue = digitalRead(flamePin);
  int analogValue = analogRead(analogPin);

  Serial.print("ค่า Digital: ");
  Serial.print(digitalValue);
  Serial.print(" | ค่า Analog: ");
  Serial.print(analogValue);

  if (digitalValue == LOW || analogValue > flameThreshold) {
    digitalWrite(ledPin, HIGH);
    tone(buzzerPin, 1000, 200);
    Serial.println(" | สถานะ: ตรวจพบเปลวไฟ");
  } else {
    digitalWrite(ledPin, LOW);
    noTone(buzzerPin);
    Serial.println(" | สถานะ: ปกติ");
  }

  delay(500);
}
