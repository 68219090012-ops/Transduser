# รหัส 68219090012 นายวัชรพล สมมี แผนกเทคนิคคอมพิวเตอร์
# รหัส 68219090016 นายพงศกร แสงหล้า แผนกเทคนิคคอมพิวเตอร์

# LAB2 Blynk2LED

โปรเจกต์นี้ใช้งานกับบอร์ด Arduino UNO เพื่อกระพริบ LED 2 ดวงพร้อมกัน

## การต่อวงจร

- LED1 ต่อขา Anode (+) เข้าที่ขา D12
- LED2 ต่อขา Anode (+) เข้าที่ขา D13
- ต่อขา Cathode (-) ของ LED แต่ละดวงเข้ากับตัวต้านทาน 220 โอห์ม หรือ 330 โอห์ม
- ต่อขาอีกด้านของตัวต้านทานเข้ากับ GND ของบอร์ด Arduino

## โค้ดตัวอย่าง

```cpp
#include <Arduino.h>

const int led1Pin = 12;
const int led2Pin = 13;
const unsigned long blinkInterval = 500;

void setup() {
  pinMode(led1Pin, OUTPUT);
  pinMode(led2Pin, OUTPUT);
}

void loop() {
  digitalWrite(led1Pin, HIGH);
  digitalWrite(led2Pin, HIGH);
  delay(blinkInterval);

  digitalWrite(led1Pin, LOW);
  digitalWrite(led2Pin, LOW);
  delay(blinkInterval);
}
```

## วิธีใช้งาน

1. ต่อ LED ตามวงจรด้านบน
2. อัพโหลดโค้ดเข้า Arduino UNO
3. LED1 และ LED2 จะกระพริบพร้อมกัน

## ข้อควรระวัง

- ตรวจสอบขั้ว LED ให้ถูกต้องก่อนต่อ
- ใช้ตัวต้านทานป้องกันไม่ให้ LED ไหม้

