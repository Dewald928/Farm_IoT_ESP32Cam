#pragma once

#include <Arduino.h>
#include <WiFi.h>           // WiFi control for ESP32
#include "config.h"

extern int status; // the Wifi radio's status

void InitWiFi();    //start up the wifi
void reconnect();   //reconnects to wifi AP
