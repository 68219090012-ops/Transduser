
#include <DHT.h>

#define DHTPIN 4
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  dht.begin();
}

void loop() {
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("อ่านค่า DHT11 ไม่สำเร็จ");
  } else {
    Serial.print("อุณหภูมิ: ");
    Serial.print(temperature);
    Serial.println(" °C");

    Serial.print("ความชื้น: ");
    Serial.print(humidity);
    Serial.println(" %RH");
  }

  delay(2000);
}


