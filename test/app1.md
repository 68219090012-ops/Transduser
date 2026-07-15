#include <Arduino.h>
#include <ESP8266WiFi.h>

const unsigned long SERIAL_BAUD = 115200;
const unsigned long REPORT_INTERVAL_MS = 3000;
const unsigned long LED_BLINK_INTERVAL_MS = 500;
const unsigned long WIFI_SCAN_INTERVAL_MS = 15000;

const uint8_t RED_LED_PIN = 0;
const uint8_t BLUE_LED_PIN = 2;
const uint8_t inputPins[] = {4, 5, 12, 13, 14, 16};

unsigned long lastReportMs = 0;
unsigned long lastLedToggleMs = 0;
unsigned long lastWifiScanMs = 0;
bool ledOn = false;

void printDivider() {
  Serial.println(F("----------------------------------------"));
}

void writeOnboardLeds(bool on) {
  // HUZZAH ESP8266 onboard LEDs are active-low.
  digitalWrite(RED_LED_PIN, on ? LOW : HIGH);
  digitalWrite(BLUE_LED_PIN, on ? LOW : HIGH);
}

void printBoardInfo() {
  Serial.println();
  printDivider();
  Serial.println(F("Adafruit Feather HUZZAH ESP8266 basic test"));
  Serial.println(F("MCU: ESP8266"));
  Serial.println(F("Logic voltage: 3.3V only - GPIO pins are not 5V tolerant"));
  Serial.println(F("Flash: 4 MB on HUZZAH board"));
  Serial.println(F("Serial Monitor baud: 115200"));
  Serial.println(F("Onboard LEDs: GPIO0 red, GPIO2 blue"));
  Serial.println(F("Input test pins: GPIO4, GPIO5, GPIO12, GPIO13, GPIO14, GPIO16"));
  Serial.println(F("Analog input: A0, maximum about 1.0V"));
  printDivider();
}

void setupPins() {
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(BLUE_LED_PIN, OUTPUT);
  writeOnboardLeds(false);

  for (uint8_t i = 0; i < sizeof(inputPins); i++) {
    pinMode(inputPins[i], INPUT_PULLUP);
  }
}

void setupWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);
}

void blinkOnboardLeds() {
  const unsigned long now = millis();

  if (now - lastLedToggleMs >= LED_BLINK_INTERVAL_MS) {
    lastLedToggleMs = now;
    ledOn = !ledOn;
    writeOnboardLeds(ledOn);
  }
}

void printChipStatus() {
  Serial.print(F("Uptime: "));
  Serial.print(millis() / 1000UL);
  Serial.println(F(" s"));

  Serial.print(F("Chip ID: 0x"));
  Serial.println(ESP.getChipId(), HEX);

  Serial.print(F("CPU frequency: "));
  Serial.print(ESP.getCpuFreqMHz());
  Serial.println(F(" MHz"));

  Serial.print(F("Flash chip size: "));
  Serial.print(ESP.getFlashChipSize() / 1024UL);
  Serial.println(F(" KB"));

  Serial.print(F("Free heap: "));
  Serial.print(ESP.getFreeHeap());
  Serial.println(F(" bytes"));

  Serial.print(F("Onboard LEDs: "));
  Serial.println(ledOn ? F("ON") : F("OFF"));
}

void printDigitalInputs() {
  Serial.println(F("GPIO inputs (INPUT_PULLUP):"));

  for (uint8_t i = 0; i < sizeof(inputPins); i++) {
    const uint8_t pin = inputPins[i];
    Serial.print(F("  GPIO"));
    Serial.print(pin);
    Serial.print(F(" = "));
    Serial.println(digitalRead(pin) == HIGH ? F("HIGH") : F("LOW"));
  }
}

void printAnalogInput() {
  Serial.print(F("A0 analog value (0-1023, max about 1.0V): "));
  Serial.println(analogRead(A0));
}

void scanWiFiIfNeeded() {
  const unsigned long now = millis();

  if (lastWifiScanMs != 0 && now - lastWifiScanMs < WIFI_SCAN_INTERVAL_MS) {
    return;
  }

  lastWifiScanMs = now;
  Serial.println(F("WiFi scan:"));

  const int networkCount = WiFi.scanNetworks();
  if (networkCount <= 0) {
    Serial.println(F("  No networks found"));
    return;
  }

  for (int i = 0; i < networkCount; i++) {
    Serial.print(F("  "));
    Serial.print(i + 1);
    Serial.print(F(". "));
    Serial.print(WiFi.SSID(i));
    Serial.print(F("  RSSI="));
    Serial.print(WiFi.RSSI(i));
    Serial.print(F(" dBm  Encryption="));
    Serial.println(WiFi.encryptionType(i) == ENC_TYPE_NONE ? F("open") : F("secured"));
  }
}

void printStatusReport() {
  printDivider();
  printChipStatus();
  printDigitalInputs();
  printAnalogInput();
  scanWiFiIfNeeded();
}

void setup() {
  Serial.begin(SERIAL_BAUD);
  delay(1000);

  setupPins();
  setupWiFi();
  printBoardInfo();
}

void loop() {
  blinkOnboardLeds();

  const unsigned long now = millis();
  if (now - lastReportMs >= REPORT_INTERVAL_MS) {
    lastReportMs = now;
    printStatusReport();
  }
}