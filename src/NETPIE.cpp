#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <EEPROM.h>
#include <StreamUtils.h>

#include "TimeManager.h"

#include "debug.h"

extern unsigned int status_manual[];

extern int check_sendData_status;
extern int check_sendData_toWeb;
extern int check_sendData_SoilMinMax;
extern int check_sendData_tempMinMax;

extern void timmer_setting(String topic, byte * payload, unsigned int length) ;
extern void TempMaxMin_setting(String topic, String message, unsigned int length) ;
extern void ControlRelay_Bymanual(String topic, String message, unsigned int length) ;
extern void SoilMaxMin_setting(String topic, String message, unsigned int length) ;

extern float Max_Soil[], Min_Soil[];
extern float Max_Temp[], Min_Temp[];

extern DynamicJsonDocument jsonDoc;

String mqtt_server ,
       mqtt_Client ,
       mqtt_password ,
       mqtt_username ,
       password ,
       mqtt_port,
       ssid ;
       
// ประกาศใช้ WiFiClient
WiFiClient espClient;
PubSubClient client(espClient);

/* --------- Callback function get data from web ---------- */
void callback(String topic, byte* payload, unsigned int length) {
  //DEBUG_PRINT("Message arrived [");
  DEBUG_PRINT("Message arrived [");
  DEBUG_PRINT(topic);
  DEBUG_PRINT("] ");
  String message;
  for (int i = 0; i < length; i++) {
    message = message + (char)payload[i];
  }
  /* ------- topic timer ------- */
  if (topic.substring(0, 14) == "@private/timer") {
    timmer_setting(topic, payload, length);
    sent_dataTimer(topic, message);
  }
  /* ------- topic manual_control relay ------- */
  else if (topic.substring(0, 12) == "@private/led") {
    status_manual[0] = 0;
    status_manual[1] = 0;
    status_manual[2] = 0;
    status_manual[3] = 0;
    ControlRelay_Bymanual(topic, message, length);
  }
  /* ------- topic Soil min max ------- */
  else if (topic.substring(0, 17) == "@private/max_temp" || topic.substring(0, 17) == "@private/min_temp") {
    TempMaxMin_setting(topic, message, length);
  }
  /* ------- topic Temp min max ------- */
  else if (topic.substring(0, 17) == "@private/max_soil" || topic.substring(0, 17) == "@private/min_soil") {
    SoilMaxMin_setting(topic, message, length);
  }
}

/* ----------------------- Sent Timer --------------------------- */
void sent_dataTimer(String topic, String message) {
  String _numberTimer = topic.substring(topic.length() - 2).c_str();
  String _payload = "{\"data\":{\"value_timer";
  _payload += _numberTimer;
  _payload += "\":\"";
  _payload += message;
  _payload += "\"}}";
  DEBUG_PRINT("incoming : "); DEBUG_PRINTLN((char*)_payload.c_str());
  client.publish("@shadow/data/update", (char*)_payload.c_str());
}

/* --------- UpdateData_To_Server --------- */
void UpdateData_To_Server() {
  String DatatoWeb;
    char msgtoWeb[200];
    DatatoWeb = "{\"data\": {\"temperature\":" + String(temp) +
                ",\"humidity\":" + String(humidity) + ",\"lux\":" +
                String(lux_44009) + ",\"soil\":" + String(soil)  + "}}";

    DEBUG_PRINT("DatatoWeb : "); DEBUG_PRINTLN(DatatoWeb);
    DatatoWeb.toCharArray(msgtoWeb, (DatatoWeb.length() + 1));
    if (client.publish("@shadow/data/update", msgtoWeb)) {
      DEBUG_PRINTLN(" Send Data Complete ");
    }
}

/* --------- sendStatus_RelaytoWeb --------- */
void sendStatus_RelaytoWeb() {
  String _payload;
  char msgUpdateRalay[200];
  if (check_sendData_status == 1) {
    _payload = "{\"data\": {\"led0\":\"" + String(RelayStatus[0]) +
               "\",\"led1\":\"" + String(RelayStatus[1]) +
               "\",\"led2\":\"" + String(RelayStatus[2]) +
               "\",\"led3\":\"" + String(RelayStatus[3]) + "\"}}";
    DEBUG_PRINT("_payload : "); DEBUG_PRINTLN(_payload);
    _payload.toCharArray(msgUpdateRalay, (_payload.length() + 1));
    if (client.publish("@shadow/data/update", msgUpdateRalay)) {
      check_sendData_status = 0;
      DEBUG_PRINTLN(" Send Complete Relay ");
    }
  }
}

/* --------- Respone soilMinMax toWeb --------- */
void send_soilMinMax() {
  String soil_payload;
  char soilMinMax_data[450];
  if (check_sendData_SoilMinMax == 1) {
    soil_payload =  "{\"data\": {\"min_soil0\":" + String(Min_Soil[0]) + ",\"max_soil0\":" + String(Max_Soil[0]) +
                    ",\"min_soil1\":" + String(Min_Soil[1]) + ",\"max_soil1\":" + String(Max_Soil[1]) +
                    ",\"min_soil2\":" + String(Min_Soil[2]) + ",\"max_soil2\":" + String(Max_Soil[2]) +
                    ",\"min_soil3\":" + String(Min_Soil[3]) + ",\"max_soil3\":" + String(Max_Soil[3]) + "}}";
    DEBUG_PRINT("_payload : "); DEBUG_PRINTLN(soil_payload);
    soil_payload.toCharArray(soilMinMax_data, (soil_payload.length() + 1));
    if (client.publish("@shadow/data/update", soilMinMax_data)) {
      check_sendData_SoilMinMax = 0;
      DEBUG_PRINTLN(" Send Complete min max ");
    }
  }
}

/* --------- Respone tempMinMax toWeb --------- */
void send_tempMinMax() {
  String temp_payload;
  char tempMinMax_data[400];
  if (check_sendData_tempMinMax == 1) {
    temp_payload =  "{\"data\": {\"min_temp0\":" + String(Min_Temp[0]) + ",\"max_temp0\":" + String(Max_Temp[0]) +
                    ",\"min_temp1\":" + String(Min_Temp[1]) + ",\"max_temp1\":" + String(Max_Temp[1]) +
                    ",\"min_temp2\":" + String(Min_Temp[2]) + ",\"max_temp2\":" + String(Max_Temp[2]) +
                    ",\"min_temp3\":" + String(Min_Temp[3]) + ",\"max_temp3\":" + String(Max_Temp[3]) + "}}";
    DEBUG_PRINT("_payload : "); DEBUG_PRINTLN(temp_payload);
    temp_payload.toCharArray(tempMinMax_data, (temp_payload.length() + 1));
    if (client.publish("@shadow/data/update", tempMinMax_data)) {
      check_sendData_tempMinMax = 0;
    }
  }
}

/* --------- Auto Connect Wifi and server and setup value init ------------- */
void TaskWifiStatus(void * pvParameters) {
  while (1) {
    WiFi.begin(ssid.c_str(), password.c_str());   
     
    while (WiFi.status() != WL_CONNECTED) {
      // DEBUG_PRINTLN("WIFI Not connect !!!");

      /* -- ESP Reset -- */
      if (millis() - time_restart > INTERVAL_MESSAGE2) { // ผ่านไป 1 ชม. ยังไม่ได้เชื่อมต่อ Wifi ให้ Reset ตัวเอง
        time_restart = millis();
        ESP.restart();
      }
      delay(100);
    }

    client.setServer(mqtt_server.c_str(), mqtt_port.toInt());
    client.setCallback(callback);

    client.connect(mqtt_Client.c_str(), mqtt_username.c_str(), mqtt_password.c_str());
    delay(100);

    while (!client.connected() ) {
      client.connect(mqtt_Client.c_str(), mqtt_username.c_str(), mqtt_password.c_str());
      DEBUG_PRINTLN("NETPIE2020 can not connect");
      delay(100);
    }

    if (client.connect(mqtt_Client.c_str(), mqtt_username.c_str(), mqtt_password.c_str())) {
      DEBUG_PRINTLN("NETPIE2020 connected");
      client.subscribe("@private/#");

      getSyncTime();
    }
    while (WiFi.status() == WL_CONNECTED) { // เชื่อมต่อ wifi แล้ว ไม่ต้องทำอะไรนอกจากส่งค่า
      //UpdateData_To_Server();
      sendStatus_RelaytoWeb();
      send_soilMinMax();
      send_tempMinMax();   
      delay(500);
    }
  }
}

void NETPIE_begin() {
  EepromStream eeprom(0, 1024);           // ประกาศ Object eepromSteam ที่ Address 0 ขนาด 1024 byte
  deserializeJson(jsonDoc, eeprom);       // คือการรับหรืออ่านข้อมูล jsonDoc ใน eeprom
  if (!jsonDoc.isNull()) {                      // ถ้าใน jsonDoc มีค่าแล้ว
    mqtt_server   = jsonDoc["server"].as<String>();
    mqtt_Client   = jsonDoc["client"].as<String>();
    mqtt_password = jsonDoc["pass"].as<String>();
    mqtt_username = jsonDoc["user"].as<String>();
    password      = jsonDoc["password"].as<String>();
    mqtt_port     = jsonDoc["port"].as<String>();
    ssid          = jsonDoc["ssid"].as<String>();
  }
  xTaskCreatePinnedToCore(TaskWifiStatus, "WifiStatus", 4096, NULL, 1, &WifiStatus, 1);
}

void NETPIE_loop() {
    client.loop();
}

