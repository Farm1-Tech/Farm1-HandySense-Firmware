#include <Arduino.h>
#include <WiFi.h>
#include <Wire.h>
#include <ArduinoJson.h>
#include <FS.h>
#include <SPIFFS.h>

#include "Farm1.h"
#include "MemConfigs.h"
#include "HandySenseWebSerial.h"
#include "NETPIE.h"
#include "TimeManager.h"
#include "SensorManager.h"
#include "RelayControl.h"
#include "Display.h"

#include "debug.h"

void timmer_setting(String topic, byte * payload, unsigned int length) ;
void SoilMaxMin_setting(String topic, String message, unsigned int length) ;
void TaskWifiStatus(void * pvParameters) ;
void sent_dataTimer(String topic, String message) ;
void ControlRelay_Bytimmer() ;
void TempMaxMin_setting(String topic, String message, unsigned int length) ;
void ControlRelay_Bymanual(String topic, String message, unsigned int length) ;

extern unsigned int time_open[4][7][3] ;
extern unsigned int time_close[4][7][3] ;

// ประกาศเพื่อเก็บข้อมูล Min Max ของค่าเซ็นเซอร์ Temp และ Soil
char msg_Minsoil[100],
     msg_Maxsoil[100];
char msg_Mintemp[100],
     msg_Maxtemp[100];

const unsigned long eventInterval             = 1 * 1000;          // อ่านค่า temp และ soil sensor ทุก ๆ 1 วินาที
const unsigned long eventInterval_brightness  = 6 * 1000;          // อ่านค่า brightness sensor ทุก ๆ 6 วินาที
unsigned long previousTime_Temp_soil          = 0;
unsigned long previousTime_brightness         = 0;

// ประกาศตัวแปรกำหนดการนับเวลาเริ่มต้น
unsigned long previousTime_Update_data        = 0;
const unsigned long eventInterval_publishData = 2 * 60 * 1000;     // เช่น 2*60*1000 ส่งทุก 2 นาที

// Array สำหรับทำ Movie Arg. ของค่าเซ็นเซอร์ทุก ๆ ค่า
float ma_temp[5];
float ma_hum[5];
float ma_soil[5];
float ma_lux[5];

// สำหรับเก็บค่าเวลาจาก Web App
int t[20];
#define state_On_Off_relay        t[0]
#define value_monday_from_Web     t[1]
#define value_Tuesday_from_Web    t[2]
#define value_Wednesday_from_Web  t[3]
#define value_Thursday_from_Web   t[4]
#define value_Friday_from_Web     t[5]
#define value_Saturday_from_Web   t[6]
#define value_Sunday_from_Web     t[7]
#define value_hour_Open           t[8]
#define value_min_Open            t[9]
#define value_hour_Close          t[11]
#define value_min_Close           t[12]

// สถานะการทำงานของ Relay ด้ววยค่า Min Max
int relayMaxsoil_status[4];
int relayMinsoil_status[4];
int relayMaxtemp_status[4];
int relayMintemp_status[4];

int check_sendData_status = 0;
int check_sendData_toWeb  = 0;
int check_sendData_SoilMinMax = 0;
int check_sendData_tempMinMax = 0;

#define INTERVAL_MESSAGE 600000 //10 นาที
#define INTERVAL_MESSAGE2 1500000 //1 ชม
unsigned long time_restart = 0;

/* ----------------------- Setting Timer --------------------------- */
void timmer_setting(String topic, byte * payload, unsigned int length) {
  int timer, relay;
  char* str;
  unsigned int count = 0;
  char message_time[50];
  timer = topic.substring(topic.length() - 1).toInt();
  relay = topic.substring(topic.length() - 2, topic.length() - 1).toInt();
  DEBUG_PRINTLN();
  DEBUG_PRINT("timeer     : "); DEBUG_PRINTLN(timer);
  DEBUG_PRINT("relay      : "); DEBUG_PRINTLN(relay);
  for (int i = 0; i < length; i++) {
    message_time[i] = (char)payload[i];
  }
  DEBUG_PRINTLN(message_time);
  str = strtok(message_time, " ,,,:");
  while (str != NULL) {
    t[count] = atoi(str);
    count++;
    str = strtok(NULL, " ,,,:");
  }
  if (state_On_Off_relay == 1) {
    for (int k = 0; k < 7; k++) {
      if (t[k + 1] == 1) {
        time_open[relay][k][timer] = (value_hour_Open * 60) + value_min_Open;
        time_close[relay][k][timer] = (value_hour_Close * 60) + value_min_Close;
      }
      else {
        time_open[relay][k][timer] = 3000;
        time_close[relay][k][timer] = 3000;
      }
      int address = ((((relay * 7 * 3) + (k * 3) + timer) * 2) * 2) + 2100;
      /*EEPROM.write(address, time_open[relay][k][timer] / 256);
      EEPROM.write(address + 1, time_open[relay][k][timer] % 256);
      EEPROM.write(address + 2, time_close[relay][k][timer] / 256);
      EEPROM.write(address + 3, time_close[relay][k][timer] % 256);
      EEPROM.commit();*/
      DEBUG_PRINT("time_open  : "); DEBUG_PRINTLN(time_open[relay][k][timer]);
      DEBUG_PRINT("time_close : "); DEBUG_PRINTLN(time_close[relay][k][timer]);
    }
  }
  else if (state_On_Off_relay == 0) {
    for (int k = 0; k < 7; k++) {
      time_open[relay][k][timer] = 3000;
      time_close[relay][k][timer] = 3000;
      int address = ((((relay * 7 * 3) + (k * 3) + timer) * 2) * 2) + 2100;
      /*EEPROM.write(address, time_open[relay][k][timer] / 256);
      EEPROM.write(address + 1, time_open[relay][k][timer] % 256);
      EEPROM.write(address + 2, time_close[relay][k][timer] / 256);
      EEPROM.write(address + 3, time_close[relay][k][timer] % 256);
      EEPROM.commit();*/
      DEBUG_PRINT("time_open  : "); DEBUG_PRINTLN(time_open[relay][k][timer]);
      DEBUG_PRINT("time_close : "); DEBUG_PRINTLN(time_close[relay][k][timer]);
    }
  }
  else {
    DEBUG_PRINTLN("Not enabled timer, Day !!!");
  }
}

/* ----------------------- SoilMaxMin_setting --------------------------- */
void SoilMaxMin_setting(String topic, String message, unsigned int length) {
  String soil_message = message;
  String soil_topic = topic;
  int Relay_SoilMaxMin = topic.substring(topic.length() - 1).toInt();
  if (soil_topic.substring(9, 12) == "max") {
    relayMaxsoil_status[Relay_SoilMaxMin] = topic.substring(topic.length() - 1).toInt();
    // Max_Soil[Relay_SoilMaxMin] = soil_message.toInt();
    //EEPROM.write(Relay_SoilMaxMin + 2000,  Max_Soil[Relay_SoilMaxMin]);
    //EEPROM.commit();
    check_sendData_SoilMinMax = 1;
    // DEBUG_PRINT("Max_Soil : "); DEBUG_PRINTLN(Max_Soil[Relay_SoilMaxMin]);
  }
  else if (soil_topic.substring(9, 12) == "min") {
    relayMinsoil_status[Relay_SoilMaxMin] = topic.substring(topic.length() - 1).toInt();
    // Min_Soil[Relay_SoilMaxMin] = soil_message.toInt();
    //EEPROM.write(Relay_SoilMaxMin + 2004,  Min_Soil[Relay_SoilMaxMin]);
    //EEPROM.commit();
    check_sendData_SoilMinMax = 1;
    // DEBUG_PRINT("Min_Soil : "); DEBUG_PRINTLN(Min_Soil[Relay_SoilMaxMin]);
  }
}

/* ----------------------- TempMaxMin_setting --------------------------- */


/* ----------------------- Set All Config --------------------------- */
void setAll_config() {
  for (int b = 0; b < 4; b++) {
    /*Max_Soil[b] = EEPROM.read(b + 2000);
    Min_Soil[b] = EEPROM.read(b + 2004);
    Max_Temp[b] = EEPROM.read(b + 2008);
    Min_Temp[b] = EEPROM.read(b + 2012);*/
    /*
    if (Max_Soil[b] >= 255) {
      Max_Soil[b] = 0;
    }
    if (Min_Soil[b] >= 255) {
      Min_Soil[b] = 0;
    }
    if (Max_Temp[b] >= 255) {
      Max_Temp[b] = 0;
    }
    if (Min_Temp[b] >= 255) {
      Min_Temp[b] = 0;
    }
    DEBUG_PRINT("Max_Soil   ");  DEBUG_PRINT(b); DEBUG_PRINT(" : "); DEBUG_PRINTLN(Max_Soil[b]);
    DEBUG_PRINT("Min_Soil   ");  DEBUG_PRINT(b); DEBUG_PRINT(" : "); DEBUG_PRINTLN(Min_Soil[b]);
    DEBUG_PRINT("Max_Temp   ");  DEBUG_PRINT(b); DEBUG_PRINT(" : "); DEBUG_PRINTLN(Max_Temp[b]);
    DEBUG_PRINT("Min_Temp   ");  DEBUG_PRINT(b); DEBUG_PRINT(" : "); DEBUG_PRINTLN(Min_Temp[b]);
    */
  }
  int count_in = 0;
  for (int eeprom_relay = 0; eeprom_relay < 4; eeprom_relay++) {
    for (int eeprom_timer = 0; eeprom_timer < 3; eeprom_timer++) {
      for (int dayinweek = 0; dayinweek < 7; dayinweek++) {
        int eeprom_address = ((((eeprom_relay * 7 * 3) + (dayinweek * 3) + eeprom_timer) * 2) * 2) + 2100;
        // time_open[eeprom_relay][dayinweek][eeprom_timer] = (EEPROM.read(eeprom_address) * 256) + (EEPROM.read(eeprom_address + 1));
        // time_close[eeprom_relay][dayinweek][eeprom_timer] = (EEPROM.read(eeprom_address + 2) * 256) + (EEPROM.read(eeprom_address + 3));

        if (time_open[eeprom_relay][dayinweek][eeprom_timer] >= 2000) {
          time_open[eeprom_relay][dayinweek][eeprom_timer] = 3000;
        }
        if (time_close[eeprom_relay][dayinweek][eeprom_timer] >= 2000) {
          time_close[eeprom_relay][dayinweek][eeprom_timer] = 3000;
        }
        DEBUG_PRINT("cout       : "); DEBUG_PRINTLN(count_in);
        DEBUG_PRINT("time_open  : "); DEBUG_PRINTLN(time_open[eeprom_relay][dayinweek][eeprom_timer]);
        DEBUG_PRINT("time_close : "); DEBUG_PRINTLN(time_close[eeprom_relay][dayinweek][eeprom_timer]);
        count_in++;
      }
    }
  }
}

void setup() {
  Serial.begin(115200);

  // Init I2C
  Wire.begin();
  Wire.setClock(10000);

  // Init SPIFFS
  if(!SPIFFS.begin(true)){
    Serial.println("SPIFFS Mount Failed");
  }

  // Init configs manager
  MemConfigs_begin();
  
  // Handle all command from HandySense via Serial
  HandySenseWebSerial_begin();
  
  // Init Sensor
  SensorManager_begin();

  // Init NETPIE
  NETPIE_begin();

  // Init RTC & NTP
  Time_begin();

  // Init Relay
  RelayControl_begin();

  // Init TFT LCD & LVGL
  Display_begin();
}

void loop() {
  SensorManager_runCycle();
  NETPIE_runCycle();
  HandySenseWebSerial_runCycle();
  RelayControl_runCycle();
  Display_runCycle();
  
  delay(1);
}
