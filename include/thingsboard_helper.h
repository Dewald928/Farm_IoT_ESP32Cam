#pragma once

#include <Arduino.h>
#include <ThingsBoard.h>
#include "config.h"

extern ThingsBoard tb;

void check_TB();   // Reconnect to ThingsBoard, if needed