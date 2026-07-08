#include <Arduino.h>
#include <LiquidCrystal.h>

// ขาต่อของเซ็นเซอร์ KY-026
const int sensorAnalogPin = A0;  // AO
const int sensorDigitalPin = 2;  // DO
const int buzzerPin = 3;         // optional buzzer
const int ledPin = 13;           // LED บนบอร์ด

// ขาต่อของ LCD 16x2
const int rs = 7;
const int en = 8;
const int d4 = 9;
const int d5 = 10;
const int d6 = 11;
const int d7 = 12;

// ค่าเกณฑ์สำหรับการแจ้งเตือน
const int threshold = 600;

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  pinMode(sensorDigitalPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(ledPin, OUTPUT);

  digitalWrite(buzzerPin, LOW);
  digitalWrite(ledPin, LOW);

  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("KY-026 Monitor");
  lcd.setCursor(0, 1);
  lcd.print("Initializing...");
  delay(1500);
}

void loop() {
  int analogValue = analogRead(sensorAnalogPin);
  int digitalValue = digitalRead(sensorDigitalPin);

  bool detected = (analogValue >= threshold) || (digitalValue == LOW);

  lcd.clear();
  lcd.setCursor(0, 0);

  if (detected) {
    digitalWrite(ledPin, HIGH);
    digitalWrite(buzzerPin, HIGH);
    lcd.print("WARNING! FIRE");
    lcd.setCursor(0, 1);
    lcd.print("Value:");
    lcd.print(analogValue);
  } else {
    digitalWrite(ledPin, LOW);
    digitalWrite(buzzerPin, LOW);
    lcd.print("Status: NORMAL");
    lcd.setCursor(0, 1);
    lcd.print("Value:");
    lcd.print(analogValue);
  }

  delay(500);
}
