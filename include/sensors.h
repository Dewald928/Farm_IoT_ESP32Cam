#pragma once

#include <Arduino.h>
#include "driver/adc.h" //for analog pin control
#include "esp32-hal-adc.h" // needed for adc pin reset
#include "soc/sens_reg.h" // needed for adc pin reset
#include "soc/soc.h"
#include "soc/rtc_cntl_reg.h"
#include <DHT.h>
#include <Wire.h> // needed?
#include <SPI.h>  // needed?
#include "config.h"
#include "ThingsBoard.h"
#include "driver/rtc_io.h"

extern uint64_t reg_b; // Used to store Pin registers
extern DHT dht;
extern ThingsBoard tb;

struct TempAndHumidity {
  float temperature;
  float humidity;
};

void ready_GPIO(); // Setup analog pins before wifi on
void LED_on(); // turns status led on
void LED_off(); // turn status led off
float get_Soil(uint64_t);  // Gets soil moisture in percentage
float get_battery_voltage(uint64_t);
float get_temperature();        // Get temp
float get_humidity();        // Get hum
TempAndHumidity get_temp_and_hum(); // gets temperature and humidity
float mapf(float , float , float , float , float );
float readVoltage(int);

