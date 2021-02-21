#pragma once

#include <Arduino.h>
#include <ThingsBoard.h>
#include "config.h"
#include <ArduinoJson.h>

extern ThingsBoard tb;
extern bool RPC_subscribed;  // Set to true if application is subscribed for the RPC messages.
extern int OTA_State;

void check_TB();   // Reconnect to ThingsBoard, if needed
void check_RPC_subscribe(); //Checks RPC messages
void log_to_tb(float, float, float, float);    // log temp, hum, soil to thingsboard
void log_attributes_tb(String, String);  // log device attributes