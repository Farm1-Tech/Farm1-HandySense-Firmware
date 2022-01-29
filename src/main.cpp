#include <Arduino.h>
#include <WiFi.h>
#include <Wire.h>
#include <ArduinoJson.h>
#include <FS.h>
#include <SPIFFS.h>

#include "HandySenseWebSerial.h"
#include "NETPIE.h"
#include "TimeManager.h"
#include "SensorManager.h"
#include "Display.h"

#include "debug.h"

void timmer_setting(String topic, byte * payload, unsigned int length) ;
void SoilMaxMin_setting(String topic, String message, unsigned int length) ;
void Get_soil() ;
void Get_sht() ;
void TaskWifiStatus(void * pvParameters) ;
void sent_dataTimer(String topic, String message) ;
void ControlRelay_Bytimmer() ;
void TempMaxMin_setting(String topic, String message, unsigned int length) ;
void ControlRelay_Bymanual(String topic, String message, unsigned int length) ;

const size_t capacity = JSON_OBJECT_SIZE(7) + 320;
DynamicJsonDocument jsonDoc(capacity);

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

float difference_soil                         = 20.00,    // ค่าความชื้นดินแตกต่างกัน +-20 % เมื่อไรส่งค่าขึ้น Web app ทันที
      difference_temp                         = 4.00;     // ค่าอุณหภูมิแตกต่างกัน +- 4 C เมื่อไรส่งค่าขึ้น Web app ทันที
float soil_old  = 0.00,
      temp_old  = 0.00;

// ประกาศตัวแปรสำหรับเก็บค่าเซ็นเซอร์
float   temp              = 0;
int     temp_error        = 0;
int     temp_error_count  = 0;

float   humidity          = 0;
int     hum_error         = 0;
int     hum_error_count   = 0;

float   lux_44009         = 0;
int     lux_error         = 0;
int     lux_error_count   = 0;

float   soil              = 0;
int     soil_error        = 0;
int     soil_error_count  = 0;

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

#define OPEN        1
#define CLOSE       0

#define Open_relay(j)    digitalWrite(relay_pin[j], HIGH)
#define Close_relay(j)   digitalWrite(relay_pin[j], LOW)

/* new PCB Red */
int relay_pin[4] = {25, 14, 12, 13};

// ตัวแปรเก็บค่าการตั้งเวลาทำงานอัตโนมัติ
unsigned int time_open[4][7][3] = {{{2000, 2000, 2000}, {2000, 2000, 2000}, {2000, 2000, 2000},
    {2000, 2000, 2000}, {2000, 2000, 2000}, {2000, 2000, 2000}, {2000, 2000, 2000}
  },
  { {2000, 2000, 2000}, {2000, 2000, 2000}, {2000, 2000, 2000},
    {2000, 2000, 2000}, {2000, 2000, 2000}, {2000, 2000, 2000}, {2000, 2000, 2000}
  },
  { {2000, 2000, 2000}, {2000, 2000, 2000}, {2000, 2000, 2000},
    {2000, 2000, 2000}, {2000, 2000, 2000}, {2000, 2000, 2000}, {2000, 2000, 2000}
  },
  { {2000, 2000, 2000}, {2000, 2000, 2000}, {2000, 2000, 2000},
    {2000, 2000, 2000}, {2000, 2000, 2000}, {2000, 2000, 2000}, {2000, 2000, 2000}
  }
};
unsigned int time_close[4][7][3] = {{{2000, 2000, 2000}, {2000, 2000, 2000}, {2000, 2000, 2000},
    {2000, 2000, 2000}, {2000, 2000, 2000}, {2000, 2000, 2000}, {2000, 2000, 2000}
  },
  { {2000, 2000, 2000}, {2000, 2000, 2000}, {2000, 2000, 2000},
    {2000, 2000, 2000}, {2000, 2000, 2000}, {2000, 2000, 2000}, {2000, 2000, 2000}
  },
  { {2000, 2000, 2000}, {2000, 2000, 2000}, {2000, 2000, 2000},
    {2000, 2000, 2000}, {2000, 2000, 2000}, {2000, 2000, 2000}, {2000, 2000, 2000}
  },
  { {2000, 2000, 2000}, {2000, 2000, 2000}, {2000, 2000, 2000},
    {2000, 2000, 2000}, {2000, 2000, 2000}, {2000, 2000, 2000}, {2000, 2000, 2000}
  }
};

float Max_Soil[4], Min_Soil[4];
float Max_Temp[4], Min_Temp[4];

unsigned int statusTimer_open[4] = {1, 1, 1, 1};
unsigned int statusTimer_close[4] = {1, 1, 1, 1};
unsigned int status_manual[4];

unsigned int statusSoil[4];
unsigned int statusTemp[4];

// สถานะการทำงานของ Relay ด้ววยค่า Min Max
int relayMaxsoil_status[4];
int relayMinsoil_status[4];
int relayMaxtemp_status[4];
int relayMintemp_status[4];

int RelayStatus[4];
TaskHandle_t WifiStatus, WaitSerial;
unsigned int oldTimer;

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
      EEPROM.write(address, time_open[relay][k][timer] / 256);
      EEPROM.write(address + 1, time_open[relay][k][timer] % 256);
      EEPROM.write(address + 2, time_close[relay][k][timer] / 256);
      EEPROM.write(address + 3, time_close[relay][k][timer] % 256);
      EEPROM.commit();
      DEBUG_PRINT("time_open  : "); DEBUG_PRINTLN(time_open[relay][k][timer]);
      DEBUG_PRINT("time_close : "); DEBUG_PRINTLN(time_close[relay][k][timer]);
    }
  }
  else if (state_On_Off_relay == 0) {
    for (int k = 0; k < 7; k++) {
      time_open[relay][k][timer] = 3000;
      time_close[relay][k][timer] = 3000;
      int address = ((((relay * 7 * 3) + (k * 3) + timer) * 2) * 2) + 2100;
      EEPROM.write(address, time_open[relay][k][timer] / 256);
      EEPROM.write(address + 1, time_open[relay][k][timer] % 256);
      EEPROM.write(address + 2, time_close[relay][k][timer] / 256);
      EEPROM.write(address + 3, time_close[relay][k][timer] % 256);
      EEPROM.commit();
      DEBUG_PRINT("time_open  : "); DEBUG_PRINTLN(time_open[relay][k][timer]);
      DEBUG_PRINT("time_close : "); DEBUG_PRINTLN(time_close[relay][k][timer]);
    }
  }
  else {
    DEBUG_PRINTLN("Not enabled timer, Day !!!");
  }
}

/* ------------ Control Relay By Timmer ------------- */
void ControlRelay_Bytimmer() {
  int curentTimer;
  int dayofweek;
  
  struct tm timeinfo = getSyncTime();
  
  curentTimer = (timeinfo.tm_hour * 60) + timeinfo.tm_min;
  dayofweek = timeinfo.tm_wday - 1;
  
  static char time_str_buff[20];
  sprintf(time_str_buff, "%02d:%02d:%02d", 
                          timeinfo.tm_hour, timeinfo.tm_min, timeinfo.tm_sec);
  /*lv_label_set_text(txtTime, time_str_buff);
  lv_obj_align(txtTime, NULL, LV_ALIGN_IN_LEFT_MID, 50, 0);*/

  //DEBUG_PRINT("curentTimer : "); DEBUG_PRINTLN(curentTimer);
  /* check curentTimer => 0-1440 */
  if ((curentTimer >= 0) && (curentTimer <= 1440)) {
    if (dayofweek == -1) {
      dayofweek = 6;
    }
    //DEBUG_PRINT("dayofweek   : "); DEBUG_PRINTLN(dayofweek);
    if (curentTimer != oldTimer) {
      for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 3; j++) {
          if (time_open[i][dayofweek][j] == curentTimer) {
            RelayStatus[i] = 1;
            check_sendData_status = 1;
            Open_relay(i);
            DEBUG_PRINTLN("timer On");
            DEBUG_PRINT("curentTimer : "); DEBUG_PRINTLN(curentTimer);
            DEBUG_PRINT("oldTimer    : "); DEBUG_PRINTLN(oldTimer);
          }
          else if (time_close[i][dayofweek][j] == curentTimer) {
            RelayStatus[i] = 0;
            check_sendData_status = 1;
            Close_relay(i);
            DEBUG_PRINTLN("timer Off");
            DEBUG_PRINT("curentTimer : "); DEBUG_PRINTLN(curentTimer);
            DEBUG_PRINT("oldTimer    : "); DEBUG_PRINTLN(oldTimer);
          }
          else if (time_open[i][dayofweek][j] == 3000 && time_close[i][dayofweek][j] == 3000) {
            //        Close_relay(i);
            //        DEBUG_PRINTLN(" Not check day, Not Working relay");
          }
        }
      }
      oldTimer = curentTimer;
    }
  }
}

/* ----------------------- Manual Control --------------------------- */
void ControlRelay_Bymanual(String topic, String message, unsigned int length) {
  String manual_message = message;
  int manual_relay = topic.substring(topic.length() - 1).toInt();
  DEBUG_PRINTLN();
  DEBUG_PRINT("manual_message : "); DEBUG_PRINTLN(manual_message);
  DEBUG_PRINT("manual_relay   : "); DEBUG_PRINTLN(manual_relay);
  if (status_manual[manual_relay] == 0) {
    status_manual[manual_relay] = 1;
    if (manual_message == "on") {
      Open_relay(manual_relay);
      RelayStatus[manual_relay] = 1;
      DEBUG_PRINTLN("ON man");
    }
    else if (manual_message == "off") {
      Close_relay(manual_relay);
      RelayStatus[manual_relay] = 0;
      DEBUG_PRINTLN("OFF man");
    }
    check_sendData_status = 1;
  }
}

/* ----------------------- SoilMaxMin_setting --------------------------- */
void SoilMaxMin_setting(String topic, String message, unsigned int length) {
  String soil_message = message;
  String soil_topic = topic;
  int Relay_SoilMaxMin = topic.substring(topic.length() - 1).toInt();
  if (soil_topic.substring(9, 12) == "max") {
    relayMaxsoil_status[Relay_SoilMaxMin] = topic.substring(topic.length() - 1).toInt();
    Max_Soil[Relay_SoilMaxMin] = soil_message.toInt();
    EEPROM.write(Relay_SoilMaxMin + 2000,  Max_Soil[Relay_SoilMaxMin]);
    EEPROM.commit();
    check_sendData_SoilMinMax = 1;
    DEBUG_PRINT("Max_Soil : "); DEBUG_PRINTLN(Max_Soil[Relay_SoilMaxMin]);
  }
  else if (soil_topic.substring(9, 12) == "min") {
    relayMinsoil_status[Relay_SoilMaxMin] = topic.substring(topic.length() - 1).toInt();
    Min_Soil[Relay_SoilMaxMin] = soil_message.toInt();
    EEPROM.write(Relay_SoilMaxMin + 2004,  Min_Soil[Relay_SoilMaxMin]);
    EEPROM.commit();
    check_sendData_SoilMinMax = 1;
    DEBUG_PRINT("Min_Soil : "); DEBUG_PRINTLN(Min_Soil[Relay_SoilMaxMin]);
  }
}

/* ----------------------- TempMaxMin_setting --------------------------- */
void TempMaxMin_setting(String topic, String message, unsigned int length) {
  String temp_message = message;
  String temp_topic = topic;
  int Relay_TempMaxMin = topic.substring(topic.length() - 1).toInt();
  if (temp_topic.substring(9, 12) == "max") {
    Max_Temp[Relay_TempMaxMin] = temp_message.toInt();
    EEPROM.write(Relay_TempMaxMin + 2008, Max_Temp[Relay_TempMaxMin]);
    EEPROM.commit();
    check_sendData_tempMinMax = 1;
    DEBUG_PRINT("Max_Temp : "); DEBUG_PRINTLN(Max_Temp[Relay_TempMaxMin]);
  }
  else if (temp_topic.substring(9, 12) == "min") {
    Min_Temp[Relay_TempMaxMin] = temp_message.toInt();
    EEPROM.write(Relay_TempMaxMin + 2012,  Min_Temp[Relay_TempMaxMin]);
    EEPROM.commit();
    check_sendData_tempMinMax = 1;
    DEBUG_PRINT("Min_Temp : "); DEBUG_PRINTLN(Min_Temp[Relay_TempMaxMin]);
  }
}

/* ----------------------- soilMinMax_ControlRelay --------------------------- */
void ControlRelay_BysoilMinMax() {
  Get_soil();
  for (int k = 0; k < 4; k++) {
    if (Min_Soil[k] != 0 && Max_Soil[k] != 0) {
      if (soil < Min_Soil[k]) {
        //DEBUG_PRINT("statusSoilMin"); DEBUG_PRINT(k); DEBUG_PRINT(" : "); DEBUG_PRINTLN(statusTemp[k]);
        if (statusSoil[k] == 0) {
          Open_relay(k);
          statusSoil[k] = 1;
          RelayStatus[k] = 1;
          check_sendData_status = 1;
          //check_sendData_toWeb = 1;
          DEBUG_PRINTLN("soil On");
        }
      }
      else if (soil > Max_Soil[k]) {
        //DEBUG_PRINT("statusSoilMax"); DEBUG_PRINT(k); DEBUG_PRINT(" : "); DEBUG_PRINTLN(statusTemp[k]);
        if (statusSoil[k] == 1) {
          Close_relay(k);
          statusSoil[k] = 0;
          RelayStatus[k] = 0;
          check_sendData_status = 1;
          //check_sendData_toWeb = 1;
          DEBUG_PRINTLN("soil Off");
        }
      }
    }
  }
}

/* ----------------------- tempMinMax_ControlRelay --------------------------- */
void ControlRelay_BytempMinMax() {
  Get_sht();
  for (int g = 0; g < 4; g++) {
    if (Min_Temp[g] != 0 && Max_Temp[g] != 0) {
      if (temp < Min_Temp[g]) {
        //DEBUG_PRINT("statusTempMin"); DEBUG_PRINT(g); DEBUG_PRINT(" : "); DEBUG_PRINTLN(statusTemp[g]);
        if (statusTemp[g] == 1) {
          Close_relay(g);
          statusTemp[g] = 0;
          RelayStatus[g] = 0;
          check_sendData_status = 1;
          //check_sendData_toWeb = 1;
          DEBUG_PRINTLN("temp Off");
        }
      }
      else if (temp > Max_Temp[g]) {
        //DEBUG_PRINT("statusTempMax"); DEBUG_PRINT(g); DEBUG_PRINT(" : "); DEBUG_PRINTLN(statusTemp[g]);
        if (statusTemp[g] == 0) {
          Open_relay(g);
          statusTemp[g] = 1;
          RelayStatus[g] = 1;
          check_sendData_status = 1;
          //check_sendData_toWeb = 1;
          DEBUG_PRINTLN("temp On");
        }
      }
    }
  }
}

/* ----------------------- Set All Config --------------------------- */
void setAll_config() {
  for (int b = 0; b < 4; b++) {
    Max_Soil[b] = EEPROM.read(b + 2000);
    Min_Soil[b] = EEPROM.read(b + 2004);
    Max_Temp[b] = EEPROM.read(b + 2008);
    Min_Temp[b] = EEPROM.read(b + 2012);
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
  }
  int count_in = 0;
  for (int eeprom_relay = 0; eeprom_relay < 4; eeprom_relay++) {
    for (int eeprom_timer = 0; eeprom_timer < 3; eeprom_timer++) {
      for (int dayinweek = 0; dayinweek < 7; dayinweek++) {
        int eeprom_address = ((((eeprom_relay * 7 * 3) + (dayinweek * 3) + eeprom_timer) * 2) * 2) + 2100;
        time_open[eeprom_relay][dayinweek][eeprom_timer] = (EEPROM.read(eeprom_address) * 256) + (EEPROM.read(eeprom_address + 1));
        time_close[eeprom_relay][dayinweek][eeprom_timer] = (EEPROM.read(eeprom_address + 2) * 256) + (EEPROM.read(eeprom_address + 3));

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
  EEPROM.begin(4096);
  Wire.begin();
  Wire.setClock(10000);

  pinMode(relay_pin[0], OUTPUT);
  pinMode(relay_pin[1], OUTPUT);
  pinMode(relay_pin[2], OUTPUT);
  pinMode(relay_pin[3], OUTPUT);
  digitalWrite(relay_pin[0], LOW);
  digitalWrite(relay_pin[1], LOW);
  digitalWrite(relay_pin[2], LOW);
  digitalWrite(relay_pin[3], LOW);
  
  // Handle all command from HandySense via Serial
  HandySenseWebSerial_begin();
  
  // Init Sensor
  SensorManager_begin();

  // Init RTC & NTP
  Time_begin();

  // Init TFT LCD & LVGL
  Display_begin();
  
  
  setAll_config();
}

void loop() {
  SensorManager_runCycle();
  NETPIE_runCycle();
  HandySenseWebSerial_runCycle();
  Display_runCycle();
  delay(1);
}
