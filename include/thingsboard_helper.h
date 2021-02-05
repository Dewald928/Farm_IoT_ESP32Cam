#pragma once

#include <Arduino.h>
#include <ThingsBoard.h>
#include "config.h"

extern ThingsBoard tb;
extern bool RPC_subscribed;  // Set to true if application is subscribed for the RPC messages.

void check_TB();   // Reconnect to ThingsBoard, if needed
void check_RPC_subscribe(); //Checks RPC messages