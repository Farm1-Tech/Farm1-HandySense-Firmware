#include <Arduino.h>
#include <ArduinoJson.h>

#include "MemConfigs.h"
#include "debug.h"

// ประกาศตัวแปรสื่อสารกับ web App
byte STX = 02;
byte ETX = 03;
uint8_t START_PATTERN[3] = { 0, 111, 222 };

void StartSendToWeb() {
  Serial.write(START_PATTERN, 3);
  Serial.write(STX);
}

void StopSendToWeb() {
  Serial.write(ETX);
}

void HandySenseWebSerial_begin() {
  Serial.setTimeout(1000); // Timeout of read from Serial

  // Send WiFi configs in SPIFFS to HandySense
  JsonObject wifiConfigs = getWiFiConfigs()->as<JsonObject>();

  // Send start to Web
  StartSendToWeb();

  // Send real content
  Serial.printf(
    "{\"ssid\": \"%s\", \"password\": \"%s\", \"server\": \"%s\", \"port\": %d, \"client\": \"%s\", \"user\": \"%s\", \"pass\": \"%s\"}",
    wifiConfigs["wifi_ssid"].as<const char*>(), 
    wifiConfigs["wifi_password"].as<const char*>(), 
    wifiConfigs["mqtt_host"].as<const char*>(), 
    wifiConfigs["mqtt_port"].as<int>(), 
    wifiConfigs["mqtt_client"].as<const char*>(), 
    wifiConfigs["mqtt_username"].as<const char*>(), 
    wifiConfigs["mqtt_password"].as<const char*>()
  );

  // Send END to Web
  StopSendToWeb();
}

void HandySenseWebSerial_runCycle() {
  if (Serial.available() > 0) {
    DynamicJsonDocument jsonDoc(2 * 1024);
    DeserializationError err = deserializeJson(jsonDoc, Serial);
    if (err == DeserializationError::Ok) {
      String command  =  jsonDoc["command"].as<String>();
      bool isValidData  =  !jsonDoc["client"].isNull();
      if (command == "restart") {
        jsonDoc.clear();
        delay(100);
        ESP.restart();
        return;
      } else {
        if (isValidData) {
          DynamicJsonDocument *wifiConfigs = getWiFiConfigs();

          // WiFi configs
          wifiConfigs->getMember("wifi_ssid").set(jsonDoc["ssid"].as<const char*>());
          wifiConfigs->getMember("wifi_password").set(jsonDoc["password"].as<const char*>());

          // MQTT configs
          wifiConfigs->getMember("mqtt_host").set(jsonDoc["server"].as<const char*>());
          wifiConfigs->getMember("mqtt_port").set(jsonDoc["port"].as<int>());
          wifiConfigs->getMember("mqtt_client").set(jsonDoc["client"].as<const char*>());
          wifiConfigs->getMember("mqtt_username").set(jsonDoc["user"].as<const char*>());
          wifiConfigs->getMember("mqtt_password").set(jsonDoc["pass"].as<const char*>());

          StartSendToWeb();
          if (SaveWiFiConfigs()) {
            serializeJson(jsonDoc, Serial);
          } else {
            Serial.printf("{\"e\": \"Save configs FAIL !\"}");
          }
          StopSendToWeb();
        } else {
          DEBUG_PRINTLN("Unknow command");
        }
      }
    } else {
      DEBUG_PRINTLN("JSON deserialize fail");
    }
  }
}
