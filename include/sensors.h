#pragma once

#include <Arduino.h>
#include "driver/adc.h" //for analog pin control
#include "esp32-hal-adc.h" // needed for adc pin reset
#include "soc/sens_reg.h" // needed for adc pin reset
#include <DHT.h>
#include <Wire.h> // needed?
#include <SPI.h>  // needed?
#include <tuple>

extern uint64_t reg_b; // Used to store Pin registers

void ready_GPIO(); // Setup analog pins before wifi on
float get_Soil(int, uint64_t);  // Gets soil moisture in percentage
float get_temperature(DHT, int);        // Get temp
float get_humidity(DHT, int);        // Get hum
void log_to_tb(float, float, float);    // log temp, hum, soil to thingsboard
