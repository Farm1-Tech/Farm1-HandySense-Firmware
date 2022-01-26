#include <Arduino.h>
#include <WiFi.h>
#include <Wire.h>
#include "Artron_DS1338.h"

#include "debug.h"

// ประกาศใช้ rtc
Artron_DS1338 rtc(&Wire);

// ประกาศใช้เวลาบน Internet
const char* ntpServer = "pool.ntp.org";
const char* nistTime = "time.nist.gov";
const long  gmtOffset_sec = 7 * 3600;
const int   daylightOffset_sec = 0;

static struct tm timeinfo;

struct tm getSyncTime() {
  bool getTimeFromInternet = false;
  if (WiFi.status() == WL_CONNECTED) {
    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer, nistTime);
    if (getLocalTime(&timeinfo)) {
      rtc.write(&timeinfo); // Sync time to RTC
      getTimeFromInternet = true;
    }
  }
  if (!getTimeFromInternet) {
    rtc.read(&timeinfo);
    DEBUG_PRINT("USE RTC 1");
  }

  return timeinfo;
}

void Time_begin() {
  rtc.begin();
}
