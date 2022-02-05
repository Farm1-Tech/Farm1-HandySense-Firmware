#include <Arduino.h>
#include <WiFi.h>
#include <Wire.h>
#include <ArduinoJson.h>

#include <EEPROM.h>
#include <StreamUtils.h>
#include "Adafruit_SHT31.h"
#include <BH1750.h>
#include "Max44009.h"
// #include "RTClib.h"
#include "time.h"
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include <Update.h>
#include <SPI.h>
#include "Artron_DS1338.h"
#include <TFT_eSPI.h>
#include <lvgl.h>

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

void Get_soil() ;
void Get_sht31() ;

void TaskWifiStatus(void * pvParameters) ;
void sent_dataTimer(String topic, String message) ;
void ControlRelay_Bytimmer() ;
void TempMaxMin_setting(String topic, String message, unsigned int length) ;
void ControlRelay_Bymanual(String topic, String message, unsigned int length) ;

extern unsigned int time_open[4][7][3] ;
extern unsigned int time_close[4][7][3] ;

#ifdef DEBUG
#define DEBUG_PRINT(x)    //Serial.print(x)
#define DEBUG_PRINTLN(x)  //Serial.println(x)
#else
#define DEBUG_PRINT(x) Serial.print(x)
#define DEBUG_PRINTLN(x) Serial.println(x)
#endif

// สร้างตัวแปรและใช้ Webserver สำหรับใช้ OTA
const char* host = "esp32";
WebServer server(80);

/*
   Login page
*/
const char* loginIndex =
  "<form name='loginForm'>"
  "<table width='20%' bgcolor='A09F9F' align='center'>"
  "<tr>"
  "<td colspan=2>"
  "<center><font size=4><b>ESP32 Login Page</b></font></center>"
  "<br>"
  "</td>"
  "<br>"
  "<br>"
  "</tr>"
  "<td>Username:</td>"
  "<td><input type='text' size=25 name='userid'><br></td>"
  "</tr>"
  "<br>"
  "<br>"
  "<tr>"
  "<td>Password:</td>"
  "<td><input type='Password' size=25 name='pwd'><br></td>"
  "<br>"
  "<br>"
  "</tr>"
  "<tr>"
  "<td><input type='submit' onclick='check(this.form)' value='Login'></td>"
  "</tr>"
  "</table>"
  "</form>"
  "<script>"
  "function check(form)"
  "{"
  "if(form.userid.value=='admin' && form.pwd.value=='admin')"
  "{"
  "window.open('/serverIndex')"
  "}"
  "else"
  "{"
  " alert('Error Password or Username')/*displays error message*/"
  "}"
  "}"
  "</script>";

/*
   Server Index Page
*/
const char* serverIndex =
  "<script src='https://ajax.googleapis.com/ajax/libs/jquery/3.2.1/jquery.min.js'></script>"
  "<form method='POST' action='#' enctype='multipart/form-data' id='upload_form'>"
  "<input type='file' name='update'>"
  "<input type='submit' value='Update'>"
  "</form>"
  "<div id='prg'>progress: 0%</div>"
  "<script>"
  "$('form').submit(function(e){"
  "e.preventDefault();"
  "var form = $('#upload_form')[0];"
  "var data = new FormData(form);"
  " $.ajax({"
  "url: '/update',"
  "type: 'POST',"
  "data: data,"
  "contentType: false,"
  "processData:false,"
  "xhr: function() {"
  "var xhr = new window.XMLHttpRequest();"
  "xhr.upload.addEventListener('progress', function(evt) {"
  "if (evt.lengthComputable) {"
  "var per = evt.loaded / evt.total;"
  "$('#prg').html('progress: ' + Math.round(per*100) + '%');"
  "}"
  "}, false);"
  "return xhr;"
  "},"
  "success:function(d, s) {"
  "console.log('success!')"
  "},"
  "error: function (a, b, c) {"
  "}"
  "});"
  "});"
  "</script>";

// ประกาศใช้ rtc
Artron_DS1338 rtc(&Wire);

// ประกาศใช้เวลาบน Internet
const char* ntpServer = "pool.ntp.org";
const char* nistTime = "time.nist.gov";
const long  gmtOffset_sec = 7 * 3600;
const int   daylightOffset_sec = 0;
int hourNow,
    minuteNow,
    secondNow,
    dayNow,
    monthNow,
    yearNow,
    weekdayNow;

struct tm timeinfo;
String _data; // อาจจะไม่ได้ใช้

// ประกาศตัวแปรสื่อสารกับ web App
byte STX = 02;
byte ETX = 03;
uint8_t START_PATTERN[3] = {0, 111, 222};
const size_t capacity = JSON_OBJECT_SIZE(7) + 320;
DynamicJsonDocument jsonDoc(capacity);

String mqtt_server ,
       mqtt_Client ,
       mqtt_password ,
       mqtt_username ,
       password ,
       mqtt_port,
       ssid ;

String client_old;

// ประกาศใช้ WiFiClient
WiFiClient espClient;
PubSubClient client(espClient);

// ประกาศใช้ WiFiUDP
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);
int curentTimerError = 0;

// ประกาศตัวแปรเรียกใช้ Max44009
// Max44009 myLux(0x4A);
BH1750 lightMeter(0x23); // ADDR connect to GND

// ประกาศตัวแปรเรียกใช้ SHT31
Adafruit_SHT31 sht31 = Adafruit_SHT31();

// ประกาศตัวแปรเก็บค่า Soil_moisture_sensor
#define Soil_moisture_sensorPin   A0
float sensorValue_soil_moisture   = 0.00,
      voltageValue_soil_moisture  = 0.00,
      percent_soil_moisture       = 0.00;
>>>>>>> parent of 300584a (Change: SHT30 -> SHT20)

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

<<<<<<< HEAD
=======
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
          digitalWrite(LEDY, HIGH);
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
          digitalWrite(LEDY, HIGH);
          //check_sendData_toWeb = 1;
          DEBUG_PRINTLN("soil Off");
        }
      }
    }
  }
}

/* ----------------------- tempMinMax_ControlRelay --------------------------- */
void ControlRelay_BytempMinMax() {
  Get_sht31();
  for (int g = 0; g < 4; g++) {
    if (Min_Temp[g] != 0 && Max_Temp[g] != 0) {
      if (temp < Min_Temp[g]) {
        //DEBUG_PRINT("statusTempMin"); DEBUG_PRINT(g); DEBUG_PRINT(" : "); DEBUG_PRINTLN(statusTemp[g]);
        if (statusTemp[g] == 1) {
          Close_relay(g);
          statusTemp[g] = 0;
          RelayStatus[g] = 0;
          check_sendData_status = 1;
          digitalWrite(LEDY, HIGH);
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
          digitalWrite(LEDY, HIGH);
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
void Get_sht31() {
  float buffer_temp = 0;
  float buffer_hum  = 0;
  float temp_cal    = 0;
  int num_temp      = 0;
  buffer_temp = sht31.readTemperature();
  buffer_hum = sht31.readHumidity();
  if (buffer_temp < -40 || buffer_temp > 125 || isnan(buffer_temp)) { // range -40 to 125 C
    if (temp_error_count >= 10) {
      temp_error = 1;
      digitalWrite(status_sht31_error, LOW);
      DEBUG_PRINT("temp_error : "); DEBUG_PRINTLN(temp_error);
    } else {
      temp_error_count++;
    }
    DEBUG_PRINT("temp_error_count  : "); DEBUG_PRINTLN(temp_error_count);
  } else {
    digitalWrite(status_sht31_error, HIGH);
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
      digitalWrite(status_sht31_error, LOW);
      DEBUG_PRINT("hum_error  : "); DEBUG_PRINTLN(hum_error);
    } else {
      hum_error_count++;
    }
    DEBUG_PRINT("hum_error_count  : "); DEBUG_PRINTLN(hum_error_count);
  } else {
    digitalWrite(status_sht31_error, HIGH);
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
      digitalWrite(status_max44009_error, LOW);
      DEBUG_PRINT("lux_error  : "); DEBUG_PRINTLN(lux_error);
    } else {
      lux_error_count++;
    }
    DEBUG_PRINT("lux_error_count  : "); DEBUG_PRINTLN(lux_error_count);
  } else {
    digitalWrite(status_max44009_error, HIGH);
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
      digitalWrite(status_soil_error, LOW);
      DEBUG_PRINT("soil_error : "); DEBUG_PRINTLN(soil_error);
    } else {
      soil_error_count++;
    }
    DEBUG_PRINT("soil_error_count  : "); DEBUG_PRINTLN(soil_error_count);
  } else {
    digitalWrite(status_soil_error, HIGH);
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

void printLocalTime() {
  if (!getLocalTime(&timeinfo)) {
    DEBUG_PRINTLN("Failed to obtain time");
    return;
  } //DEBUG_PRINTLN(&timeinfo, "%A, %d %B %Y %H:%M:%S");
}
>>>>>>> parent of 300584a (Change: SHT30 -> SHT20)

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
<<<<<<< HEAD
=======
  rtc.begin();
  lightMeter.begin(BH1750::CONTINUOUS_HIGH_RES_MODE);
  pinMode(Soil_moisture_sensorPin, INPUT);
  pinMode(relay_pin[0], OUTPUT);
  pinMode(relay_pin[1], OUTPUT);
  pinMode(relay_pin[2], OUTPUT);
  pinMode(relay_pin[3], OUTPUT);
  pinMode(LEDR, OUTPUT);
  pinMode(LEDY, OUTPUT);
  pinMode(connect_WifiStatusToBox,    OUTPUT);
  pinMode(status_sht31_error,         OUTPUT);
  pinMode(status_max44009_error,      OUTPUT);
  pinMode(status_soil_error,          OUTPUT);
  digitalWrite(connect_WifiStatusToBox, HIGH);
  digitalWrite(status_sht31_error,      HIGH);
  digitalWrite(status_max44009_error,   HIGH);
  digitalWrite(status_soil_error,       HIGH);
  digitalWrite(relay_pin[0], LOW);
  digitalWrite(relay_pin[1], LOW);
  digitalWrite(relay_pin[2], LOW);
  digitalWrite(relay_pin[3], LOW);
  if (!sht31.begin(0x44)) {
    Serial.println("Init SHT31 error, Sensor not connect ?");
  }
  for (int x = 0; x < 20; x++) {
    digitalWrite(LEDY, 0);    digitalWrite(LEDR, 1);    delay(50);
    digitalWrite(LEDY, 1);    digitalWrite(LEDR, 0);    delay(50);
  }
  digitalWrite(LEDY, HIGH);     digitalWrite(LEDR, HIGH);

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

  /*Initialize the (dummy) input device driver*/
  lv_indev_drv_t indev_drv;
  lv_indev_drv_init(&indev_drv);
  indev_drv.type = LV_INDEV_TYPE_POINTER;
  indev_drv.read_cb = my_input_read;
  lv_indev_drv_register(&indev_drv);
>>>>>>> parent of 300584a (Change: SHT30 -> SHT20)

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

<<<<<<< HEAD
  // Init TFT LCD & LVGL
  Display_begin();
=======
  Edit_device_wifi();
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
  xTaskCreatePinnedToCore(TaskWaitSerial, "WaitSerial", 8192, NULL, 1, &WaitSerial, 1);
  setAll_config();
  delay(500);
  sensorValue_soil_moisture = analogRead(Soil_moisture_sensorPin);
  voltageValue_soil_moisture = (sensorValue_soil_moisture * 3.3) / (4095.00);
  ma_soil[0] = ma_soil[1] = ma_soil[2] = ma_soil[3] = ma_soil[4] = ((-58.82) * voltageValue_soil_moisture) + 123.52;
  ma_temp[0] =  ma_temp[1] =  ma_temp[2] =  ma_temp[3] =  ma_temp[4] = sht31.readTemperature();
  ma_hum[0] = ma_hum[1] = ma_hum[2] = ma_hum[3] = ma_hum[4] = sht31.readHumidity();
  // ma_lux[0] = ma_lux[1] = ma_lux[2] = ma_lux[3] = ma_lux[4] = myLux.getLux() / 1000;
  ma_lux[0] = ma_lux[1] = ma_lux[2] = ma_lux[3] = ma_lux[4] = lightMeter.readLightLevel() / 1000; // lux to klux
>>>>>>> parent of 300584a (Change: SHT30 -> SHT20)
}

void loop() {
  SensorManager_runCycle();
  NETPIE_runCycle();
  HandySenseWebSerial_runCycle();
  RelayControl_runCycle();
  Display_runCycle();
  
  delay(1);
}
