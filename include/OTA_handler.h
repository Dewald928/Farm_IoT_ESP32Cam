#pragma once

#include <ESPmDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>   

void start_OTA();   //enables Over the air updates
void check_OTA(int);   //does not sleep if OTA enabled