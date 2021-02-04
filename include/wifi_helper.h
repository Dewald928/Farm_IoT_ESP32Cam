#pragma once

#include <Arduino.h>
#include <WiFi.h>           // WiFi control for ESP32
#include "config.h"
#include <esp_wifi.h>

extern int wifi_status; // the Wifi radio's status

void InitWiFi();    //start up the wifi
void reconnect();   //reconnects to wifi AP
void check_WiFi();  // Reconnect to WiFi, if needed
