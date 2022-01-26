#include <Arduino.h>
#include <WiFi.h>
#include <Wire.h>
#include <NTPClient.h>
#include <PubSubClient.h>
#include <WiFiUdp.h>
#include <ArduinoJson.h>
#include <EEPROM.h>
#include <StreamUtils.h>
// #include "Adafruit_SHT31.h"
#include <BH1750.h>
#include "Max44009.h"
// #include "RTClib.h"
#include "time.h"
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include <Update.h>
#include <SPI.h>
#include "Artron_SHT20.h"
#include <TFT_eSPI.h>
#include <lvgl.h>
#include <lv_qrcode.h>

#include "HandySenseWebSerial.h"
#include "NETPIE.h"
#include "TimeManager.h"

#include "debug.h"

#define LCD_BL_PIN 32

TFT_eSPI tft = TFT_eSPI();

static lv_disp_buf_t disp_buf;
static lv_color_t buf[LV_HOR_RES_MAX * 10];

/* Display flushing */
void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p) {
  uint32_t w = (area->x2 - area->x1 + 1);
  uint32_t h = (area->y2 - area->y1 + 1);

  tft.startWrite();
  tft.setAddrWindow(area->x1, area->y1, w, h);
  tft.pushColors(&color_p->full, w * h, true);
  tft.endWrite();

  lv_disp_flush_ready(disp);
}


struct {
  uint16_t max_x = 0;
  uint16_t max_y = 0;
  uint16_t min_x = 0;
  uint16_t min_y = 0;
} TouchCalibration;

bool my_input_read(lv_indev_drv_t * drv, lv_indev_data_t*data) {
  uint16_t x = 0, y = 0;
  // bool touched = tft.getTouch(&x, &y, 500);

  // uint16_t x, y;
  tft.getTouchRaw(&y, &x); // Axis wrong
  bool touched = (x > 10) && (y > 10);
  // Serial.printf("raw_x: %5d\traw_y: %5d\n", x, y);

  x = map(x, TouchCalibration.min_x, TouchCalibration.max_x, 28, 320 - 28);
  y = map(y, TouchCalibration.min_y, TouchCalibration.max_y, 28, 240 - 28);

  if (touched) {
    uint16_t xOld = x, yOld = y;
    y += 22.0 / 152.0 * xOld;
    //Serial.printf("Press: %d, %d\n", x, y);
    delay(50);
  } else {
    //Serial.println("No Press");
  }

  data->point.x = x;
  data->point.y = y;
  data->state = touched ? LV_INDEV_STATE_PR : LV_INDEV_STATE_REL;
  
  return false; /*No buffering now so no more data read*/
}

extern void load_page_main() ;

extern lv_obj_t* MainScreen;

extern lv_obj_t* txtTime;
extern lv_obj_t* imgWiFi;
extern lv_obj_t* imgNexpie;

extern lv_obj_t* txtTemp;
extern lv_obj_t* txtHumi;
extern lv_obj_t* txtHumi2;
extern lv_obj_t* txtLight;

extern void load_page_settings() ;

extern lv_obj_t* SettingsScreen;

extern lv_obj_t* objBoxQRCode;
lv_obj_t* wifiConnectQRCode;

extern lv_obj_t* txtWiFiSSID;
extern lv_obj_t* txtWiFiPassword;

extern void load_page_touch_calibration() ;
extern lv_obj_t* TouchCalibrationScreen;

extern lv_obj_t* objTopLeftTouchPoint;
extern lv_obj_t* objBottomLeftTouchPoint;
extern lv_obj_t* objBottomRightTouchPoint;
extern lv_obj_t* objRightLeftTouchPoint;

extern lv_obj_t* txtTouchCalibrationStep;
extern lv_obj_t* txtTouchCalibrationCountdown;

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

// ประกาศตัวแปรเรียกใช้ Max44009
// Max44009 myLux(0x4A);
BH1750 lightMeter(0x23); // ADDR connect to GND

// ประกาศตัวแปรเรียกใช้ SHT31
// Adafruit_SHT31 sht31 = Adafruit_SHT31();
Artron_SHT20 sht(&Wire);

// ประกาศตัวแปรเก็บค่า Soil_moisture_sensor
#define Soil_moisture_sensorPin   A0
float sensorValue_soil_moisture   = 0.00,
      voltageValue_soil_moisture  = 0.00,
      percent_soil_moisture       = 0.00;

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
  lv_label_set_text(txtTime, time_str_buff);
  lv_obj_align(txtTime, NULL, LV_ALIGN_IN_LEFT_MID, 50, 0);

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

/* ----------------------- Mode for calculator sensor i2c --------------------------- */
int Mode(float* getdata) {
  int maxValue = 0;
  int maxCount = 0;
  for (int i = 0; i < sizeof(getdata); ++i) {
    int count = 0;
    for (int j = 0; j < sizeof(getdata); ++j) {
      if (round(getdata[j]) == round(getdata[i]))
        ++count;
    }
    if (count > maxCount) {
      maxCount = count;
      maxValue = round(getdata[i]);
    }
  }
  return maxValue;
}

/* ----------------------- Calculator sensor SHT31  --------------------------- */
void Get_sht() {
  float buffer_temp = 0;
  float buffer_hum  = 0;
  float temp_cal    = 0;
  int num_temp      = 0;
  buffer_temp = sht.readTemperature();
  buffer_hum = sht.readHumidity();
  if (buffer_temp < -40 || buffer_temp > 125 || isnan(buffer_temp)) { // range -40 to 125 C
    if (temp_error_count >= 10) {
      temp_error = 1;
      DEBUG_PRINT("temp_error : "); DEBUG_PRINTLN(temp_error);
    } else {
      temp_error_count++;
    }
    DEBUG_PRINT("temp_error_count  : "); DEBUG_PRINTLN(temp_error_count);
  } else {
    ma_temp[4] = ma_temp[3];
    ma_temp[3] = ma_temp[2];
    ma_temp[2] = ma_temp[1];
    ma_temp[1] = ma_temp[0];
    ma_temp[0] = buffer_temp;

    int mode_value_temp = Mode(ma_temp);
    for (int i = 0; i < sizeof(ma_temp); i++) {
      if (abs(mode_value_temp - ma_temp[i]) < 1) {
        temp_cal = temp_cal + ma_temp[i];
        num_temp++;
      }
    }
    temp = temp_cal / num_temp;
    temp_error = 0;
    temp_error_count = 0;
  }
  float hum_cal     = 0;
  int num_hum       = 0;
  if (buffer_hum < 0 || buffer_hum > 100  || isnan(buffer_hum)) { // range 0 to 100 %RH
    if (hum_error_count >= 10) {
      hum_error = 1;
      DEBUG_PRINT("hum_error  : "); DEBUG_PRINTLN(hum_error);
    } else {
      hum_error_count++;
    }
    DEBUG_PRINT("hum_error_count  : "); DEBUG_PRINTLN(hum_error_count);
  } else {
    ma_hum[4] = ma_hum[3];
    ma_hum[3] = ma_hum[2];
    ma_hum[2] = ma_hum[1];
    ma_hum[1] = ma_hum[0];
    ma_hum[0] = buffer_hum;

    int mode_value_hum = Mode(ma_hum);
    for (int j = 0; j < sizeof(ma_hum); j++) {
      if (abs(mode_value_hum - ma_hum[j]) < 1) {
        hum_cal = hum_cal + ma_hum[j];
        num_hum++;
      }
    }
    humidity = hum_cal / num_hum;
    hum_error = 0;
    hum_error_count = 0;
  }
}

/* ----------------------- Calculator sensor Max44009 --------------------------- */
void Get_max44009() {
  float buffer_lux  = 0;
  float lux_cal     = 0;
  int num_lux       = 0;
  // buffer_lux = myLux.getLux() / 1000;
  buffer_lux = lightMeter.readLightLevel() / 1000.0; // lux to klux

  if (buffer_lux < 0 || buffer_lux > 188000 || isnan(buffer_lux)) { // range 0.045 to 188,000 lux
    if (lux_error_count >= 10) {
      lux_error = 1;
      DEBUG_PRINT("lux_error  : "); DEBUG_PRINTLN(lux_error);
    } else {
      lux_error_count++;
    }
    DEBUG_PRINT("lux_error_count  : "); DEBUG_PRINTLN(lux_error_count);
  } else {
    ma_lux[4] = ma_lux[3];
    ma_lux[3] = ma_lux[2];
    ma_lux[2] = ma_lux[1];
    ma_lux[1] = ma_lux[0];
    ma_lux[0] = buffer_lux;

    int mode_value_lux = Mode(ma_lux);
    for (int i = 0; i < sizeof(ma_lux); i++) {
      if (abs(mode_value_lux - ma_lux[i]) < 1) {
        lux_cal = lux_cal + ma_lux[i];
        num_lux++;
      }
    }
    lux_44009 = lux_cal / num_lux;
    lux_error = 0;
    lux_error_count = 0;
  }
}

/* ----------------------- Calculator sensor Soil  --------------------------- */
void Get_soil() {
  float buffer_soil = 0;
  sensorValue_soil_moisture = analogRead(Soil_moisture_sensorPin);
  voltageValue_soil_moisture = (sensorValue_soil_moisture * 3.3) / (4095.00);
  buffer_soil = ((-58.82) * voltageValue_soil_moisture) + 123.52;
  if (buffer_soil < 0 || buffer_soil > 100 || isnan(buffer_soil)) { // range 0 to 100 %
    if (soil_error_count >= 10) {
      soil_error = 1;
      DEBUG_PRINT("soil_error : "); DEBUG_PRINTLN(soil_error);
    } else {
      soil_error_count++;
    }
    DEBUG_PRINT("soil_error_count  : "); DEBUG_PRINTLN(soil_error_count);
  } else {
    ma_soil[4] = ma_soil[3];
    ma_soil[3] = ma_soil[2];
    ma_soil[2] = ma_soil[1];
    ma_soil[1] = ma_soil[0];
    ma_soil[0] = buffer_soil;
    soil = (ma_soil[0] + ma_soil[1] + ma_soil[2] + ma_soil[3] + ma_soil[4]) / 5;
    if (soil <= 0) {
      soil = 0;
    }
    else if (soil >= 100) {
      soil = 100;
    }
    soil_error = 0;
    soil_error_count = 0;
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


void btnGoToSettingsHandle(lv_obj_t *obj, lv_event_t event) {
  if(event == LV_EVENT_CLICKED) {
    String qr_code_str = "WIFI:T:WPA;S:Farm1;P:123456789;;";
    lv_qrcode_update(wifiConnectQRCode, (char*)qr_code_str.c_str(), qr_code_str.length());
    lv_scr_load(SettingsScreen);
  }
}

void SettingsScreenGoBackHandle(lv_obj_t *obj, lv_event_t event) {
  if(event == LV_EVENT_CLICKED) {
    lv_scr_load(MainScreen);
  }
}

void do_touch_calibration() {
  uint8_t state = 0;
  uint16_t i = 0;
  uint32_t posXsum = 0, posYsum = 0;
  uint8_t posSample = 0;
  while(1) {
    lv_task_handler(); /* let the GUI do its work */
    
    uint16_t x, y;
    // tft.getTouchRaw(&x, &y);
    tft.getTouchRaw(&y, &x); // Axis wrong
    // Serial.printf("x: %5d\ty: %5d\n", x, y);
    /* Serial.printf("x: %i     ", x);
    Serial.printf("y: %i     ", y);
    Serial.printf("z: %i \n", tft.getTouchRawZ());*/
    bool isPressed = (x > 0) && (y > 0);
    
    if (state == 0) {
      // Hide all point
      lv_obj_set_hidden(objTopLeftTouchPoint, true);
      lv_obj_set_hidden(objBottomLeftTouchPoint, true);
      lv_obj_set_hidden(objBottomRightTouchPoint, true);
      lv_obj_set_hidden(objRightLeftTouchPoint, true);
      
      lv_label_set_text(txtTouchCalibrationStep, "");

      // Hide countdown
      lv_obj_set_hidden(txtTouchCalibrationCountdown, true);

      // Show touch calibration screen
      lv_scr_load(TouchCalibrationScreen);
      state = 1;
    }
    if (state == 1) {
      lv_obj_set_hidden(objTopLeftTouchPoint, false);
      lv_label_set_text(txtTouchCalibrationStep, "กดจุดด้านบนซ้ายค้างไว้");
      lv_obj_align(txtTouchCalibrationStep, NULL, LV_ALIGN_CENTER, 0, 0);

      state = 2;
    }
    if (state == 2) {
      if (isPressed) {
        lv_label_set_text(txtTouchCalibrationStep, "กดค้างไว้ซักครู่");
        lv_obj_align(txtTouchCalibrationStep, NULL, LV_ALIGN_CENTER, 0, 0);

        i = 0;
        posXsum = 0;
        posYsum = 0;
        posSample = 0;
        state = 3;
      }
    }
    if (state == 3) {
      if (isPressed) {
        if (i >= 20) {
          posXsum += x;
          posYsum += y;
          posSample++;
          if (posSample >= 10) {
            TouchCalibration.min_x = (float)posXsum / (float)posSample;
            TouchCalibration.min_y = (float)posYsum / (float)posSample;

            lv_label_set_text(txtTouchCalibrationStep, "หยุดกดจุด");
            lv_obj_align(txtTouchCalibrationStep, NULL, LV_ALIGN_CENTER, 0, 0);
            lv_obj_set_hidden(objTopLeftTouchPoint, true);

            i = 0;
            state = 4;
          }
        }
        i++;
      } else {
        state = 1;
      }
    }
    if (state == 4) {
      if (!isPressed) {
        i++;
        if (i > 100) {
          state = 5;
        }
      }
    }
    if (state == 5) {
      lv_obj_set_hidden(objBottomRightTouchPoint, false);
      lv_label_set_text(txtTouchCalibrationStep, "กดจุดด้านล่างขวาค้างไว้");
      lv_obj_align(txtTouchCalibrationStep, NULL, LV_ALIGN_CENTER, 0, 0);

      state = 6;
    }
    if (state == 6) {
      if (isPressed) {
        lv_label_set_text(txtTouchCalibrationStep, "กดค้างไว้ซักครู่");
        lv_obj_align(txtTouchCalibrationStep, NULL, LV_ALIGN_CENTER, 0, 0);

        i = 0;
        posXsum = 0;
        posYsum = 0;
        posSample = 0;
        state = 7;
      }
    }
    if (state == 7) {
      if (isPressed) {
        if (i >= 20) {
          posXsum += x;
          posYsum += y;
          posSample++;
          if (posSample >= 10) {
            TouchCalibration.max_x = (float)posXsum / (float)posSample;
            TouchCalibration.max_y = (float)posYsum / (float)posSample;

            lv_label_set_text(txtTouchCalibrationStep, "หยุดกดจุด");
            lv_obj_align(txtTouchCalibrationStep, NULL, LV_ALIGN_CENTER, 0, 0);
            lv_obj_set_hidden(objBottomRightTouchPoint, true);

            i = 0;
            state = 8;
          }
        }
        i++;
      } else {
        state = 5;
      }
    }
    if (state == 8) {
      if (!isPressed) {
        i++;
        if (i > 100) {
          state = 9;
        }
      }
    }
    if (state == 9) {
      Serial.printf("min_x: %5d\tmin_y: %5d\n", TouchCalibration.min_x, TouchCalibration.min_y);
      Serial.printf("min_x: %5d\tmin_y: %5d\n", TouchCalibration.max_x, TouchCalibration.max_y);
      break;
    }

    delay(5);
  }
}

void setup() {
  Serial.begin(115200);
  EEPROM.begin(4096);
  Wire.begin();
  Wire.setClock(10000);
  
  lightMeter.begin(BH1750::CONTINUOUS_HIGH_RES_MODE);
  pinMode(Soil_moisture_sensorPin, INPUT);
  pinMode(relay_pin[0], OUTPUT);
  pinMode(relay_pin[1], OUTPUT);
  pinMode(relay_pin[2], OUTPUT);
  pinMode(relay_pin[3], OUTPUT);
  digitalWrite(relay_pin[0], LOW);
  digitalWrite(relay_pin[1], LOW);
  digitalWrite(relay_pin[2], LOW);
  digitalWrite(relay_pin[3], LOW);
  // if (!sht31.begin(0x44)) {
  if (!sht.begin()) {
    Serial.println("Init SHT20 error, Sensor not connect ?");
  }

  tft.begin(); /* TFT init */
  tft.setRotation(3); /* Landscape orientation */

  lv_init();

  lv_disp_buf_init(&disp_buf, buf, NULL, LV_HOR_RES_MAX * 10);

  /*Initialize the display*/
  lv_disp_drv_t disp_drv;
  lv_disp_drv_init(&disp_drv);
  disp_drv.hor_res = 320;
  disp_drv.ver_res = 240;
  disp_drv.flush_cb = my_disp_flush;
  disp_drv.buffer = &disp_buf;
  lv_disp_drv_register(&disp_drv);

  load_page_main();
  load_page_settings();
  load_page_touch_calibration();

  // Set all label
  lv_label_set_text(txtTime, "LOADING");
  lv_obj_align(txtTime, NULL, LV_ALIGN_IN_LEFT_MID, 20, 0);

  lv_obj_set_hidden(imgWiFi, false);
  lv_obj_set_hidden(imgNexpie, false);

  lv_label_set_text(txtTemp, "");
  lv_obj_align(txtTemp, NULL, LV_ALIGN_IN_BOTTOM_RIGHT, -30, -37);

  lv_label_set_text(txtHumi, "");
  lv_obj_align(txtHumi, NULL, LV_ALIGN_IN_BOTTOM_RIGHT, -23, -38);

  lv_label_set_text(txtHumi2, "");
  lv_obj_align(txtHumi2, NULL, LV_ALIGN_IN_BOTTOM_RIGHT, -24, -38);

  lv_label_set_text(txtLight, "");
  lv_obj_align(txtLight, NULL, LV_ALIGN_IN_BOTTOM_RIGHT, -47, -38);

  pinMode(LCD_BL_PIN, OUTPUT);
  digitalWrite(LCD_BL_PIN, LOW);

  do_touch_calibration();

  /*Initialize the (dummy) input device driver*/
  lv_indev_drv_t indev_drv;
  lv_indev_drv_init(&indev_drv);
  indev_drv.type = LV_INDEV_TYPE_POINTER;
  indev_drv.read_cb = my_input_read;
  lv_indev_drv_register(&indev_drv);

  lv_scr_load(MainScreen);
  // lv_scr_load(SettingsScreen);

  wifiConnectQRCode = lv_qrcode_create(objBoxQRCode, 150, lv_color_hex(0x000000), lv_color_hex(0xFFFFFF));
  lv_obj_align(wifiConnectQRCode, NULL, LV_ALIGN_CENTER, 0, 0);
  
  // Handle all command from HandySense via Serial
  HandySenseWebSerial_begin();

  
  
  setAll_config();
  // delay(500);
  sensorValue_soil_moisture = analogRead(Soil_moisture_sensorPin);
  voltageValue_soil_moisture = (sensorValue_soil_moisture * 3.3) / (4095.00);
  ma_soil[0] = ma_soil[1] = ma_soil[2] = ma_soil[3] = ma_soil[4] = ((-58.82) * voltageValue_soil_moisture) + 123.52;
  ma_temp[0] =  ma_temp[1] =  ma_temp[2] =  ma_temp[3] =  ma_temp[4] = sht.readTemperature();
  ma_hum[0] = ma_hum[1] = ma_hum[2] = ma_hum[3] = ma_hum[4] = sht.readHumidity();
  // ma_lux[0] = ma_lux[1] = ma_lux[2] = ma_lux[3] = ma_lux[4] = myLux.getLux() / 1000;
  ma_lux[0] = ma_lux[1] = ma_lux[2] = ma_lux[3] = ma_lux[4] = lightMeter.readLightLevel() / 1000; // lux to klux
}

void loop() {
  lv_task_handler(); /* let the GUI do its work */
  

  delay(1);
  unsigned long currentTime = millis();
  if (currentTime - previousTime_Temp_soil >= eventInterval) {
    ControlRelay_Bytimmer();
    ControlRelay_BysoilMinMax();
    ControlRelay_BytempMinMax();

    DEBUG_PRINTLN("");
    DEBUG_PRINT("Temp : ");       DEBUG_PRINT(temp);      DEBUG_PRINT(" C, ");
    DEBUG_PRINT("Hum  : ");       DEBUG_PRINT(humidity);  DEBUG_PRINT(" %RH, ");
    DEBUG_PRINT("Brightness : "); DEBUG_PRINT(lux_44009); DEBUG_PRINT(" Klux, ");
    DEBUG_PRINT("Soil  : ");      DEBUG_PRINT(soil);      DEBUG_PRINTLN(" %");

    lv_label_set_text(txtTemp, String(temp, 1).c_str());
    lv_obj_align(txtTemp, NULL, LV_ALIGN_IN_BOTTOM_RIGHT, -30, -37);

    lv_label_set_text(txtHumi, String(humidity, 1).c_str());
    lv_obj_align(txtHumi, NULL, LV_ALIGN_IN_BOTTOM_RIGHT, -23, -38);

    lv_label_set_text(txtHumi2, String(soil, 1).c_str());
    lv_obj_align(txtHumi2, NULL, LV_ALIGN_IN_BOTTOM_RIGHT, -24, -38);

    lv_label_set_text(txtLight, String(lux_44009, 1).c_str());
    lv_obj_align(txtLight, NULL, LV_ALIGN_IN_BOTTOM_RIGHT, -47, -38);

    previousTime_Temp_soil = currentTime;
  }
  static unsigned long previousTime_wifi_connect = 0;
  if ((previousTime_wifi_connect == 0) || ((currentTime - previousTime_wifi_connect) >= 300)) {
    if (WiFi.isConnected()) {
      lv_obj_set_hidden(imgWiFi, false);
      /*if (client.connected()) {
        lv_obj_set_hidden(imgNexpie, false);
      } else {
        lv_obj_set_hidden(imgNexpie, !lv_obj_get_hidden(imgNexpie));
      }*/
    } else {
      lv_obj_set_hidden(imgWiFi, !lv_obj_get_hidden(imgWiFi));
      lv_obj_set_hidden(imgNexpie, true);
    }
    previousTime_wifi_connect = currentTime;
  }
  if (currentTime - previousTime_brightness >= eventInterval_brightness) {
    Get_max44009();
    previousTime_brightness = currentTime;
  }
  unsigned long currentTime_Update_data = millis();
  if (previousTime_Update_data == 0 || (currentTime_Update_data - previousTime_Update_data >= (eventInterval_publishData))) {
    //check_sendData_toWeb = 1;
    UpdateData_To_Server();
    previousTime_Update_data = currentTime_Update_data;
    soil_old = soil;
    temp_old = temp;
  }
}


