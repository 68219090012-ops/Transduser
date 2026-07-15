# 🔥 ระบบตรวจจับเปลวไฟด้วยเซ็นเซอร์ KY-026 และ Arduino Uno

## 📌 รายละเอียดโครงงาน

โครงงานนี้เป็นระบบตรวจจับเปลวไฟโดยใช้เซ็นเซอร์ **KY-026 Flame Sensor Module** ร่วมกับ **Arduino Uno** และแสดงผลผ่าน **LCD 16x2 แบบ I2C** เมื่อเซ็นเซอร์ตรวจพบเปลวไฟ ระบบจะแสดงข้อความแจ้งเตือนบนหน้าจอ LCD และเปิดไฟ LED บนบอร์ด Arduino เพื่อแจ้งเตือนผู้ใช้งาน

---

## 🎯 วัตถุประสงค์

- ศึกษาการทำงานของเซ็นเซอร์ตรวจจับเปลวไฟ KY-026
- เรียนรู้การเชื่อมต่อเซ็นเซอร์กับ Arduino Uno
- แสดงผลสถานะผ่าน LCD 16x2 แบบ I2C
- แจ้งเตือนเมื่อพบเปลวไฟด้วย LED

---

## 🛠 อุปกรณ์ที่ใช้

| อุปกรณ์ | จำนวน |
|----------|-------|
| Arduino Uno R3 | 1 |
| KY-026 Flame Sensor Module | 1 |
| LCD 16x2 พร้อม I2C Module | 1 |
| สาย Jumper | ตามความเหมาะสม |
| USB Cable | 1 |

---

## 🔌 การเชื่อมต่อวงจร

### KY-026

| KY-026 | Arduino Uno |
|--------|-------------|
| VCC | 5V |
| GND | GND |
| AO | A3 |
| DO | D7 |

### LCD I2C

| LCD I2C | Arduino Uno |
|----------|-------------|
| VCC | 5V |
| GND | GND |
| SDA | A4 |
| SCL | A5 |

### LED

ใช้ LED บนบอร์ด Arduino Uno

| LED | Arduino |
|-----|----------|
| Built-in LED | D13 |

---

## ⚙️ หลักการทำงาน

1. Arduino อ่านค่าจากขา Analog (A3) และ Digital (D7)
2. เปรียบเทียบค่าที่อ่านได้กับ Threshold
3. หากตรวจพบเปลวไฟ
   - เปิด LED บนบอร์ด
   - แสดงข้อความ **WARNING! FIRE**
4. หากไม่พบเปลวไฟ
   - ปิด LED
   - แสดงข้อความ **Status: NORMAL**
5. ระบบจะตรวจสอบค่าทุก ๆ 500 มิลลิวินาที

---

## 💻 ไลบรารีที่ใช้

- Arduino Framework
- Wire
- LiquidCrystal_I2C

### PlatformIO

เพิ่มในไฟล์ `platformio.ini`

```ini
lib_deps =
    marcoschwartz/LiquidCrystal_I2C
```

---

## 📂 โครงสร้างโปรเจกต์

```
Project
│
├── src
│   └── main.cpp
│
├── include
│
├── lib
│
├── platformio.ini
│
└── README.md
```

---

## ▶️ การทำงานของโปรแกรม

เริ่มต้นระบบ

↓

แสดงข้อความ "Initializing"

↓

อ่านค่า Analog และ Digital จาก KY-026

↓

ตรวจสอบค่าเซ็นเซอร์

↓

พบเปลวไฟ ?

├── ใช่
│   ├── เปิด LED
│   └── แสดง WARNING! FIRE
│
└── ไม่ใช่
    ├── ปิด LED
    └── แสดง Status: NORMAL

↓

วนทำงานตลอดเวลา

---

## 📸 ตัวอย่างการแสดงผล

### เมื่อไม่พบเปลวไฟ

```
Status: NORMAL
Value: 245
```

### เมื่อพบเปลวไฟ

```
WARNING! FIRE
Value: 812
```

---

## 📖 ผู้พัฒนา

จัดทำเพื่อการศึกษาและทดลองใช้งานเซ็นเซอร์ **KY-026 Flame Sensor Module** ร่วมกับ **Arduino Uno** และ **PlatformIO**