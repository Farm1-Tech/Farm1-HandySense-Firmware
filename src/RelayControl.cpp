#include <Arduino.h>

#include "Farm1.h"
#include "NETPIE.h"
#include "SensorManager.h"
#include "TimeManager.h"

#include "debug.h"

int relay_pin[4] = { O1, O2, O3, O4 };

float Max_Soil[4], Min_Soil[4];
float Max_Temp[4], Min_Temp[4];

// ตัวแปรเก็บค่าการตั้งเวลาทำงานอัตโนมัติ
unsigned int time_open[4][7][3] = {
  {
    {2000, 2000, 2000}, {2000, 2000, 2000}, {2000, 2000, 2000},
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
unsigned int time_close[4][7][3] = {
  {
    {2000, 2000, 2000}, {2000, 2000, 2000}, {2000, 2000, 2000},
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

unsigned int statusSoil[4];
unsigned int statusTemp[4];

void Relay_Set(int n, bool status) {
  digitalWrite(relay_pin[n], status);
}

bool Relay_Get(int n) {
  return digitalRead(relay_pin[n]) == HIGH;
}

/* ----------------------- Manual Control --------------------------- */
void ControlRelay_Bymanual(String topic, String message, unsigned int length) {
  String manual_message = message;
  int relay_num = topic.substring(topic.length() - 1).toInt();
  Relay_Set(relay_num, manual_message == "on");
  NETPIE_SendRealyStatus();
}

/* ----------------------- soilMinMax_ControlRelay --------------------------- */
void ControlRelay_BysoilMinMax() {
  bool send_status_update = false;
  for (int k = 0; k < 4; k++) {
    if (Min_Soil[k] != 0 && Max_Soil[k] != 0) {
      if (Sensor_get_soil() < Min_Soil[k]) {
        //DEBUG_PRINT("statusSoilMin"); DEBUG_PRINT(k); DEBUG_PRINT(" : "); DEBUG_PRINTLN(statusTemp[k]);
        if (statusSoil[k] == 0) {
          Relay_Set(k, true);
          statusSoil[k] = 1;
          send_status_update = true;
          DEBUG_PRINTLN("soil On");
        }
      }
      else if (Sensor_get_soil() > Max_Soil[k]) {
        //DEBUG_PRINT("statusSoilMax"); DEBUG_PRINT(k); DEBUG_PRINT(" : "); DEBUG_PRINTLN(statusTemp[k]);
        if (statusSoil[k] == 1) {
          Relay_Set(k, false);
          statusSoil[k] = 0;
          send_status_update = true;
          DEBUG_PRINTLN("soil Off");
        }
      }
    }
  }
  if (send_status_update) {
    NETPIE_SendRealyStatus();
  }
}

/* ----------------------- tempMinMax_ControlRelay --------------------------- */
void ControlRelay_BytempMinMax() {
  bool send_status_update = false;
  for (int g = 0; g < 4; g++) {
    if (Min_Temp[g] != 0 && Max_Temp[g] != 0) {
      if (Sensor_get_temp() < Min_Temp[g]) {
        //DEBUG_PRINT("statusTempMin"); DEBUG_PRINT(g); DEBUG_PRINT(" : "); DEBUG_PRINTLN(statusTemp[g]);
        if (statusTemp[g] == 1) {
          Relay_Set(g, false);
          statusTemp[g] = 0;
          send_status_update = true;
          DEBUG_PRINTLN("temp Off");
        }
      }
      else if (Sensor_get_temp() > Max_Temp[g]) {
        //DEBUG_PRINT("statusTempMax"); DEBUG_PRINT(g); DEBUG_PRINT(" : "); DEBUG_PRINTLN(statusTemp[g]);
        if (statusTemp[g] == 0) {
          Relay_Set(g, true);
          statusTemp[g] = 1;
          send_status_update = true;
          DEBUG_PRINTLN("temp On");
        }
      }
    }
  }
  if (send_status_update) {
    NETPIE_SendRealyStatus();
  }
}

unsigned int oldTimer;

/* ------------ Control Relay By Timmer ------------- */
void ControlRelay_Bytimmer() {
  bool send_status_update = false;

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
            // RelayStatus[i] = 1;
            Relay_Set(i, true);
            DEBUG_PRINTLN("timer On");
            DEBUG_PRINT("curentTimer : "); DEBUG_PRINTLN(curentTimer);
            DEBUG_PRINT("oldTimer    : "); DEBUG_PRINTLN(oldTimer);

            send_status_update = true;
          }
          else if (time_close[i][dayofweek][j] == curentTimer) {
            // RelayStatus[i] = 0;
            Relay_Set(i, false);
            DEBUG_PRINTLN("timer Off");
            DEBUG_PRINT("curentTimer : "); DEBUG_PRINTLN(curentTimer);
            DEBUG_PRINT("oldTimer    : "); DEBUG_PRINTLN(oldTimer);

            send_status_update = true;
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

  if (send_status_update) {
    NETPIE_SendRealyStatus();
  }
}

void RelayControl_begin() {
  // Setup relay pin to OUTPUT
  pinMode(relay_pin[0], OUTPUT);
  pinMode(relay_pin[1], OUTPUT);
  pinMode(relay_pin[2], OUTPUT);
  pinMode(relay_pin[3], OUTPUT);
}

void RelayControl_runCycle() {
  
}
