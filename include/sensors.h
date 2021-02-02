#pragma once

#include <Arduino.h>
#include "driver/adc.h" //for analog pin control
#include "esp32-hal-adc.h" // needed for adc pin reset
#include "soc/sens_reg.h" // needed for adc pin reset

extern uint64_t reg_b; // Used to store Pin registers

void ready_GPIO();  // Setup analog pins before wifi on
float get_Soil(int, uint64_t);
