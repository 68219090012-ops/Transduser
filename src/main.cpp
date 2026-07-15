#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define AO_PIN A3

LiquidCrystal_I2C lcd(0x27, 16, 2);

// ปรับค่า Threshold ตามค่าที่อ่านได้จริง
const int threshold = 500;

void setup() {

  Serial.begin(9600);

  lcd.init();
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print("KY-026 Monitor");
  lcd.setCursor(0, 1);
  lcd.print("System Ready");
  delay(2000);

  lcd.clear();
}

void loop() {

  // อ่านค่าจากเซ็นเซอร์
  int analogValue = analogRead(AO_PIN);

  // แสดงค่าใน Serial Monitor
  Serial.print("Analog = ");
  Serial.println(analogValue);

  // ตรวจสอบการพบเปลวไฟ
  if (analogValue < threshold) {

    lcd.setCursor(0, 0);
    lcd.print("WARNING! FIRE ");

  } else {

    lcd.setCursor(0, 0);
    lcd.print("Status: NORMAL");
  }

  // แสดงค่าเซ็นเซอร์
  lcd.setCursor(0, 1);
  lcd.print("Value:");
  lcd.print(analogValue);
  lcd.print("    ");

  delay(300);
}