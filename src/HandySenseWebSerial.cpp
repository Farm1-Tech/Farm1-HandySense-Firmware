#include <Arduino.h>
#include <ArduinoJson.h>
#include <EEPROM.h>
#include <StreamUtils.h>

String client_old;

// ประกาศตัวแปรสื่อสารกับ web App
byte STX = 02;
byte ETX = 03;
uint8_t START_PATTERN[3] = {0, 111, 222};
extern DynamicJsonDocument jsonDoc;

/* ----------------------- Delete All Config --------------------------- */
void Delete_All_config() {
  for (int b = 2000; b < 4096; b++) {
    EEPROM.write(b, 255);
    EEPROM.commit();
  }
}

/* -------- webSerialJSON function ------- */
void webSerialJSON() {
  while (Serial.available() > 0) {
    Serial.setTimeout(10000);
    EepromStream eeprom(0, 1024);
    DeserializationError err = deserializeJson(jsonDoc, Serial);
    if (err == DeserializationError::Ok) {
      String command  =  jsonDoc["command"].as<String>();
      bool isValidData  =  !jsonDoc["client"].isNull();
      if (command == "restart") {
        delay(100);
        ESP.restart();
      }
      if (isValidData) {
        /* ------------------WRITING----------------- */
        serializeJson(jsonDoc, eeprom);
        eeprom.flush();
        // ถ้าไม่เหมือนคือเพิ่มอุปกรณ์ใหม่ // ถ้าเหมือนคือการเปลี่ยน wifi
        if (client_old != jsonDoc["client"].as<String>()) {
          Delete_All_config();
        }
        delay(100);
        ESP.restart();
      }
    }  else  {
      Serial.read();
    }
  }
}

/* ----------------------- Add and Edit device || Edit Wifi --------------------------- */
void Edit_device_wifi() {
  EepromStream eeprom(0, 1024);
  Serial.write(START_PATTERN, 3);               // ส่งข้อมูลชนิดไบต์ ส่งตัวอักษรไปบนเว็บ
  Serial.flush();                               // เครียบัฟเฟอร์ให้ว่าง
  deserializeJson(jsonDoc, eeprom);             // คือการรับหรืออ่านข้อมูล jsonDoc ใน eeprom
  client_old = jsonDoc["client"].as<String>();  // เก็บค่า client เก่าเพื่อเช็คกับ client ใหม่ ในการ reset Wifi ไม่ให้ลบค่า Config อื่นๆ
  Serial.write(STX);                            // 02 คือเริ่มส่ง
  serializeJsonPretty(jsonDoc, Serial);         // ส่งข่อมูลของ jsonDoc ไปบนเว็บ
  Serial.write(ETX);
  delay(1000);
  Serial.write(START_PATTERN, 3);               // ส่งข้อมูลชนิดไบต์ ส่งตัวอักษรไปบนเว็บ
  Serial.flush();
  jsonDoc["server"]   = NULL;
  jsonDoc["client"]   = NULL;
  jsonDoc["pass"]     = NULL;
  jsonDoc["user"]     = NULL;
  jsonDoc["password"] = NULL;
  jsonDoc["port"]     = NULL;
  jsonDoc["ssid"]     = NULL;
  jsonDoc["command"]  = NULL;
  Serial.write(STX);                      // 02 คือเริ่มส่ง
  serializeJsonPretty(jsonDoc, Serial);   // ส่งข่อมูลของ jsonDoc ไปบนเว็บ
  Serial.write(ETX);                      // 03 คือจบ
}

void HandySenseWebSerial_begin() {
  Edit_device_wifi();
}

void HandySenseWebSerial_runCycle() {
  webSerialJSON();
}
