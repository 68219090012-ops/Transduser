# Transduser

โปรเจกต์นี้ใช้งานกับบอร์ด Arduino UNO และทำให้ LED 2 ดวงกระพริบด้วยกัน

## อุปกรณ์

- Arduino UNO
- LED 2 ดวง
- ตัวต้านทาน 220 โอห์ม หรือ 330 โอห์ม 2 ตัว
- สายไฟ

## การต่อวงจร

- LED1 ต่อขา Anode (+) เข้าที่ขา D12 ของบอร์ด Arduino
- LED2 ต่อขา Anode (+) เข้าที่ขา D13 ของบอร์ด Arduino
- ขา Cathode (-) ของ LED แต่ละดวงต่อเข้ากับขาตัวต้านทาน
- ต่ออีกข้างของตัวต้านทานเข้ากับ GND ของ Arduino

> หมายเหตุ: ถ้าใช้ LED แบบมีขาสั้น/ยาว ให้ขาด้านสั้นเป็นขา Cathode (-) และขาด้านยาวเป็นขา Anode (+)

## ตัวอย่างโค้ด

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

1. ต่อวงจรตามคำอธิบายด้านบน
2. เปิดโปรเจกต์ด้วย PlatformIO
3. กด Upload เพื่ออัพโหลดโค้ดเข้า Arduino UNO
4. เมื่ออัพโหลดเสร็จ LED1 และ LED2 จะกระพริบพร้อมกัน

## ข้อควรระวัง

- ตรวจสอบขั้ว LED ให้ถูกต้องก่อนต่อ
- ใช้ตัวต้านทานป้องกันไม่ให้ LED ไหม้
