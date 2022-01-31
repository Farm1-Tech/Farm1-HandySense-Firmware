#include <MemConfigs.h>
#include "Arduino.h"
#include <FS.h>
#include <SPIFFS.h>

#define WIFI_CONFIGS_FILE "/wifi.json"
#define WORK_CONFIGS_FILE "/work.json"

static DynamicJsonDocument jsonDocWiFiConfigs(2 * 1024);
static DynamicJsonDocument jsonDocWorkConfigs(4 * 1024);

#define OPEN_FILE(file_name, mode) ({ \
                              file = SPIFFS.open(file_name, mode); \
                              if(!file || file.isDirectory()){ \
                                Serial.printf("%s failed to open file for writing\n", file_name); \
                                return false; \
                              } \
                            })

bool SaveWiFiConfigs() {
  File file;
  OPEN_FILE(WIFI_CONFIGS_FILE, FILE_WRITE);
  serializeJson(jsonDocWiFiConfigs, file);
  // Serial.print("Write to file: ");
  // serializeJson(jsonDocWiFiConfigs, Serial);
  file.close();

  return true;
}

DynamicJsonDocument *getWiFiConfigs() {
  return &jsonDocWiFiConfigs;
}

bool SaveWorkConfigs() {
  File file;
  OPEN_FILE(WORK_CONFIGS_FILE, FILE_WRITE);
  serializeJson(jsonDocWorkConfigs, file);
  // Serial.print("Write to file: ");
  // serializeJson(jsonDocWorkConfigs, Serial);
  file.close();

  return true;
}

DynamicJsonDocument *getWorkConfigs() {
  return &jsonDocWorkConfigs;
}

#define ASSINGED_IF_NULL(key)   ({ \
                                  if (jsonDocWiFiConfigs[key].isNull()) { \
                                    jsonDocWiFiConfigs[key] = (const char*)""; \
                                  } \
                                })

bool MemConfigs_begin() {
  // Init SPIFFS
  if(!SPIFFS.begin(true)){
    Serial.println("SPIFFS Mount Failed");
  }
  
  // Call WiFi configs from SPIFFS
  File file;
  OPEN_FILE(WIFI_CONFIGS_FILE, FILE_READ);
  deserializeJson(jsonDocWiFiConfigs, file);
  file.close();

  ASSINGED_IF_NULL("wifi_ssid");
  ASSINGED_IF_NULL("wifi_password");
  ASSINGED_IF_NULL("mqtt_host");
  ASSINGED_IF_NULL("mqtt_port");
  ASSINGED_IF_NULL("mqtt_client");
  ASSINGED_IF_NULL("mqtt_username");
  ASSINGED_IF_NULL("mqtt_password");
  
  // Call Work configs from SPIFFS
  OPEN_FILE(WORK_CONFIGS_FILE, FILE_READ);
  deserializeJson(jsonDocWorkConfigs, file);
  file.close();

  if (jsonDocWorkConfigs["temp_max"].isNull()) {
    JsonArray temp_max = jsonDocWorkConfigs["temp_max"].to<JsonArray>();
    for (uint8_t i=0;i<4;i++) {
      temp_max.add(0);
    }
  }
  if (jsonDocWorkConfigs["temp_min"].isNull()) {
    JsonArray temp_min = jsonDocWorkConfigs["temp_min"].to<JsonArray>();
    for (uint8_t i=0;i<4;i++) {
      temp_min.add(0);
    }
  }

  return true;
}
