#include <Arduino.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <WiFiManager.h>

constexpr uint8_t LED_PIN = LED_BUILTIN;
constexpr unsigned long STATUS_INTERVAL_MS = 10000;
constexpr unsigned long MQTT_RETRY_MS = 5000;
constexpr char BOARD_ID[] = "transduser-01";
constexpr char MQTT_BROKER[] = "broker.hivemq.com";
constexpr uint16_t MQTT_PORT = 1883;
constexpr char MQTT_BASE_TOPIC[] = "transduser";

WiFiClient espClient;
PubSubClient mqttClient(espClient);
WiFiManager wifiManager;

unsigned long lastStatusMs = 0;
unsigned long lastMqttPublishMs = 0;
bool ledState = false;
String telemetryTopic;
String controlTopic;

void configModeCallback(WiFiManager *manager) {
  (void)manager;
  Serial.println(F("Config portal started"));
  digitalWrite(LED_PIN, LOW);
}

void saveConfigCallback() {
  Serial.println(F("New Wi-Fi credentials saved"));
}

void printWiFiStatus() {
  Serial.println();
  Serial.println(F("=== WiFi Manager ==="));
  Serial.print(F("SSID: "));
  Serial.println(WiFi.SSID());
  Serial.print(F("IP: "));
  Serial.println(WiFi.localIP());
  Serial.print(F("RSSI: "));
  Serial.println(WiFi.RSSI());
  Serial.println(F("===================="));
}

void buildTopics() {
  telemetryTopic = String(MQTT_BASE_TOPIC) + "/" + BOARD_ID + "/telemetry";
  controlTopic = String(MQTT_BASE_TOPIC) + "/" + BOARD_ID + "/control";
}

void callback(char *topic, byte *payload, unsigned int length) {
  String message;
  for (unsigned int i = 0; i < length; ++i) {
    message += (char)payload[i];
  }

  Serial.print(F("MQTT message on "));
  Serial.print(topic);
  Serial.print(F(": "));
  Serial.println(message);

  if (String(topic) == controlTopic) {
    if (message.equalsIgnoreCase("on") || message == "1" || message.equalsIgnoreCase("true")) {
      digitalWrite(LED_PIN, LOW);
      ledState = true;
    } else if (message.equalsIgnoreCase("off") || message == "0" || message.equalsIgnoreCase("false")) {
      digitalWrite(LED_PIN, HIGH);
      ledState = false;
    } else if (message.equalsIgnoreCase("toggle")) {
      ledState = !ledState;
      digitalWrite(LED_PIN, ledState ? LOW : HIGH);
    }
  }
}

void reconnectMqtt() {
  while (!mqttClient.connected()) {
    Serial.print(F("Attempting MQTT connection..."));
    String clientId = String("ESP8266-") + BOARD_ID + "-" + String(random(0xffff), HEX);

    if (mqttClient.connect(clientId.c_str())) {
      Serial.println(F("MQTT connected"));
      mqttClient.subscribe(controlTopic.c_str());
      mqttClient.publish(telemetryTopic.c_str(), "online", true);
    } else {
      Serial.print(F("failed, rc="));
      Serial.print(mqttClient.state());
      Serial.println(F(" retrying in 5 seconds"));
      delay(MQTT_RETRY_MS);
    }
  }
}

void publishTelemetry() {
  char payload[160];
  snprintf(payload, sizeof(payload),
           "{\"board_id\":\"%s\",\"rssi\":%d,\"heap\":%u,\"uptime_ms\":%lu,\"led\":%s}",
           BOARD_ID,
           WiFi.RSSI(),
           ESP.getFreeHeap(),
           millis(),
           ledState ? "true" : "false");

  mqttClient.publish(telemetryTopic.c_str(), payload, true);
}

void setup() {
  Serial.begin(115200);
  delay(1000);

  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, HIGH);
  ledState = false;

  wifiManager.setAPCallback(configModeCallback);
  wifiManager.setSaveConfigCallback(saveConfigCallback);
  wifiManager.setConfigPortalTimeout(180);

  bool connected = wifiManager.autoConnect("ESP8266-Config", "12345678");
  if (!connected) {
    Serial.println(F("Wi-Fi connection failed. Restarting..."));
    delay(3000);
    ESP.restart();
  }

  Serial.println(F("Wi-Fi connected"));
  printWiFiStatus();

  buildTopics();
  mqttClient.setServer(MQTT_BROKER, MQTT_PORT);
  mqttClient.setCallback(callback);
  reconnectMqtt();
}

void loop() {
  wifiManager.process();

  const unsigned long now = millis();

  if (now - lastStatusMs >= STATUS_INTERVAL_MS) {
    lastStatusMs = now;
    printWiFiStatus();
  }

  if (!mqttClient.connected()) {
    reconnectMqtt();
  } else {
    mqttClient.loop();
  }

  if (now - lastMqttPublishMs >= STATUS_INTERVAL_MS) {
    lastMqttPublishMs = now;
    publishTelemetry();
  }
}
