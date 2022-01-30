#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <EEPROM.h>
#include <StreamUtils.h>

#include "Farm1.h"
#include "TimeManager.h"
#include "SensorManager.h"
#include "MemConfigs.h"

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
       
WiFiClient espClient;
PubSubClient client(espClient);

TaskHandle_t NETPIEManagerTaskHandle;

void sent_dataTimer(String topic, String message) ;

/* --------- Callback function get data from web ---------- */
void callback(String topic, byte* payload, unsigned int length) {
  //DEBUG_PRINT("Message arrived [");
  DEBUG_PRINT("Message arrived [");
  DEBUG_PRINT(topic);
  DEBUG_PRINT("] ");
  String message;
  for (int i=0;i<length;i++) {
    message = message + (char)payload[i];
  }
  /* ------- topic timer ------- */
  if (topic.startsWith("@private/timer")) {
    timmer_setting(topic, payload, length);
    sent_dataTimer(topic, message);
  }
  /* ------- topic manual_control relay ------- */
  else if (topic.startsWith("@private/led")) {
    status_manual[0] = 0;
    status_manual[1] = 0;
    status_manual[2] = 0;
    status_manual[3] = 0;
    ControlRelay_Bymanual(topic, message, length);
  }
  /* ------- topic Soil min max ------- */
  else if (topic.startsWith("@private/max_temp") || topic.startsWith("@private/min_temp")) {
    TempMaxMin_setting(topic, message, length);
  }
  /* ------- topic Temp min max ------- */
  else if (topic.startsWith("@private/max_soil") || topic.startsWith("@private/min_soil")) {
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
  String _payload = "{\"data\": {" \
                      "\"temperature\":" + String(Sensor_get_temp()) + ","
                      "\"humidity\":" + String(Sensor_get_humi()) + "," 
                      "\"lux\":" + String(Sensor_get_lux() / 1000.0) + ","
                      "\"soil\":" + String(Sensor_get_soil()) + \
                    "}}";
  DEBUG_PRINT("DatatoWeb : ");
  DEBUG_PRINTLN(_payload);
  if (client.publish("@shadow/data/update", _payload.c_str())) {
    DEBUG_PRINTLN(" Send Data Complete ");
  }
}

/* --------- sendStatus_RelaytoWeb --------- */
void sendStatus_RelaytoWeb() {
  if (check_sendData_status == 1) {
    String _payload = "{\"data\": {\"led0\":\"" + String(digitalRead(O1)) +
               "\",\"led1\":\"" + String(digitalRead(O2)) +
               "\",\"led2\":\"" + String(digitalRead(O3)) +
               "\",\"led3\":\"" + String(digitalRead(O4)) + "\"}}";
    DEBUG_PRINT("_payload : ");
    DEBUG_PRINTLN(_payload);
    if (client.publish("@shadow/data/update", _payload.c_str())) {
      check_sendData_status = 0;
      DEBUG_PRINTLN(" Send Complete Relay ");
    }
  }
}

/* --------- Respone soilMinMax toWeb --------- */
void send_soilMinMax() {
  if (check_sendData_SoilMinMax == 1) {
    String soil_payload =  "{\"data\": {\"min_soil0\":" + String(Min_Soil[0]) + ",\"max_soil0\":" + String(Max_Soil[0]) +
                           ",\"min_soil1\":" + String(Min_Soil[1]) + ",\"max_soil1\":" + String(Max_Soil[1]) +
                           ",\"min_soil2\":" + String(Min_Soil[2]) + ",\"max_soil2\":" + String(Max_Soil[2]) +
                           ",\"min_soil3\":" + String(Min_Soil[3]) + ",\"max_soil3\":" + String(Max_Soil[3]) + "}}";
    DEBUG_PRINT("soil_payload : ");
    DEBUG_PRINTLN(soil_payload);
    if (client.publish("@shadow/data/update", soil_payload.c_str())) {
      check_sendData_SoilMinMax = 0;
      DEBUG_PRINTLN(" Send Complete min max ");
    }
  }
}

/* --------- Respone tempMinMax toWeb --------- */
void send_tempMinMax() {
  if (check_sendData_tempMinMax == 1) {
    String temp_payload =  "{\"data\": {\"min_temp0\":" + String(Min_Temp[0]) + ",\"max_temp0\":" + String(Max_Temp[0]) +
                           ",\"min_temp1\":" + String(Min_Temp[1]) + ",\"max_temp1\":" + String(Max_Temp[1]) +
                           ",\"min_temp2\":" + String(Min_Temp[2]) + ",\"max_temp2\":" + String(Max_Temp[2]) +
                           ",\"min_temp3\":" + String(Min_Temp[3]) + ",\"max_temp3\":" + String(Max_Temp[3]) + "}}";
    DEBUG_PRINT("temp_payload : ");
    DEBUG_PRINTLN(temp_payload);
    if (client.publish("@shadow/data/update", temp_payload.c_str())) {
      check_sendData_tempMinMax = 0;
    }
  }
}

bool wifiDisconnectFlag = false;

void WiFiEvent(WiFiEvent_t event) {
  Serial.printf("[WiFi-event] event: %d\n", event);

  switch (event) {
    case SYSTEM_EVENT_STA_STOP:
    case SYSTEM_EVENT_STA_DISCONNECTED:
    case SYSTEM_EVENT_STA_LOST_IP: {
      Serial.println("WiFi lost connect");
      wifiDisconnectFlag = true;
      break;
    }
    case SYSTEM_EVENT_STA_GOT_IP: {
      Serial.print("WiFi Connected, ");
      Serial.println(WiFi.localIP());
      wifiDisconnectFlag = false;
      break;
    }
    default: break;
  }
}

void NETPIEManagerTask(void*) {
  WiFi.onEvent(WiFiEvent);
  WiFi.mode(WIFI_STA);

  client.setBufferSize(4 * 1024); // 4 kBytes
  client.setCallback(callback);

  // Get WiFi Configs
  DynamicJsonDocument *wifiConfigs = getWiFiConfigs();

  while (1) {
    delay(20);

    if (!WiFi.isConnected()) {
      wifiDisconnectFlag = false;
      const char* wifiSSID = wifiConfigs->getMember("wifi_ssid").as<const char*>();
      const char* wifiPassword = wifiConfigs->getMember("wifi_password").as<const char*>();

      if ((!wifiSSID) || (*wifiSSID == 0) || (strlen(wifiSSID) <= 0)) {
        // Serial.printf("WiFi Name: %s\n", wifiSSID);
        // DEBUG_PRINTLN("WiFi not configs");
        delay(100);
        continue;
      }

      // Start WiFi connect
      if (WiFi.begin(wifiSSID, strlen(wifiPassword) > 5 ? wifiPassword : NULL) == WL_CONNECT_FAILED) {
        DEBUG_PRINTLN("WiFi begin fail");
        delay(500);
        continue;
      }
      
      // Wait WiFi connect or disconnect
      while(!WiFi.isConnected()) {
        if (wifiDisconnectFlag) {
          break;
        }
        delay(10);
      }

      // If WiFi not connect and disconnect flag is SET
      if ((!WiFi.isConnected()) && wifiDisconnectFlag) {
        WiFi.disconnect();
        continue;
      }
    }

    if (!client.connected()) {
      const char* mqttHost = wifiConfigs->getMember("mqtt_host").as<const char*>();
      int mqttPort = wifiConfigs->getMember("mqtt_port").as<int>();
      const char* mqttClient = wifiConfigs->getMember("mqtt_client").as<const char*>();
      const char* mqttUsername = wifiConfigs->getMember("mqtt_username").as<const char*>();
      const char* mqttPassword = wifiConfigs->getMember("mqtt_password").as<const char*>();

      Serial.print("Attempting MQTT connection... ");
      client.setServer(mqttHost, mqttPort);
      if (client.connect(mqttClient, mqttUsername, mqttPassword)) {
        Serial.println("connected");

        // Subscribe
        client.subscribe("@private/#");

        // Sync time
        getSyncTime();
      } else {
        Serial.printf("failed, rc=%d try again in 5 seconds\n", client.state());
        delay(5000);
        continue;
      }
    } else {
      static uint64_t update_data_timer = 0;
      if (((millis() - update_data_timer) >= 1000) || (update_data_timer == 0)) {
        UpdateData_To_Server();
        sendStatus_RelaytoWeb();
        send_soilMinMax();
        send_tempMinMax();  

        update_data_timer = millis();
      }
    }

    client.loop();
  }

  vTaskDelete(NULL);
}

void NETPIE_begin() {
  xTaskCreatePinnedToCore(NETPIEManagerTask, "NETPIEManagerTask", 4096, NULL, 1, &NETPIEManagerTaskHandle, 1);
}

void NETPIE_runCycle() {
  // client.loop();
}

