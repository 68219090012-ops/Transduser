# ออกแบบวิธีการทดสอบ Sensor เพื่อแสดงผลที่ Serial Monitor

## 1. วัตถุประสงค์
การทดสอบเซ็นเซอร์มีวัตถุประสงค์เพื่อยืนยันว่าเซ็นเซอร์ทำงานถูกต้องและสามารถส่งข้อมูลไปแสดงผลบน Serial Monitor ได้อย่างถูกต้อง โดยเฉพาะในโครงงานที่ต้องการตรวจสอบค่าที่เซ็นเซอร์รับรู้จากสิ่งแวดล้อม

## 2. อุปกรณ์ที่ใช้
- บอร์ด Arduino / ESP32
- เซ็นเซอร์ KY-026 (Flame Sensor)
- สายจองต่อ
- คอมพิวเตอร์พร้อมโปรแกรม Arduino IDE หรือ PlatformIO
- Serial Monitor เพื่อดูผลลัพธ์

## 3. วิธีการต่ออุปกรณ์
| อุปกรณ์ | การต่อ |
|---|---|
| VCC | ต่อกับ 5V |
| GND | ต่อกับ GND |
| DO | ต่อกับขา Digital โดยตัวอย่างคือ D2 |
| AO | ต่อกับขา Analog โดยตัวอย่างคือ A0 |

## 4. ขั้นตอนการทดสอบ
1. ต่อเซ็นเซอร์เข้ากับบอร์ดตามตารางด้านบน
2. เปิดโปรแกรมพัฒนาและเลือกบอร์ดที่ใช้
3. พิมพ์โค้ดเพื่ออ่านค่าจากเซ็นเซอร์
4. อัปโหลดโค้ดลงบอร์ด
5. เปิด Serial Monitor ที่ baud rate 9600
6. ตรวจสอบค่าที่แสดงผลบนจอ

## 5. ตัวอย่างโค้ดสำหรับแสดงผลบน Serial Monitor
```cpp
int flamePin = 2;      // ขา DO
int analogPin = A0;    // ขา AO

void setup() {
  pinMode(flamePin, INPUT);
  Serial.begin(9600);
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
```

## 6. วิธีประเมินผล
- หากเซ็นเซอร์รับแสงหรือเปลวไฟ จะทำให้ค่า digitalValue เปลี่ยนแปลง
- ค่า analogValue จะเปลี่ยนตามความเข้มของแสงที่ตรวจจับได้
- ถ้าไม่เห็นค่าที่เปลี่ยนแปลง ให้ตรวจสอบการต่อสายและความถูกต้องของขาเชื่อมต่อ

## 7. ตัวอย่างผลลัพธ์ที่คาดหวัง
```text
Digital Value: 0 | Analog Value: 320
Digital Value: 0 | Analog Value: 450
Digital Value: 1 | Analog Value: 100
```

## 8. สรุป
การทดสอบเซ็นเซอร์โดยแสดงผลผ่าน Serial Monitor เป็นวิธีที่ง่ายและเหมาะสมสำหรับตรวจสอบว่าเซ็นเซอร์ทำงานถูกต้องหรือไม่ การอ่านค่าแบบดิจิทัลและแอนะล็อกช่วยให้เข้าใจพฤติกรรมของเซ็นเซอร์ได้ชัดเจนขึ้น
