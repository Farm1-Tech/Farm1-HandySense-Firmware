#pragma once
#include <ArduinoJson.h>

bool MemConfigs_begin() ;
bool SaveWiFiConfigs() ;
DynamicJsonDocument *getWiFiConfigs() ;
