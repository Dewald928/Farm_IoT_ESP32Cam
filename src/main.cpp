#include <Arduino.h>
#include "sensors.h"
#include "wifi_helper.h"
#include "config.h"
#include "thingsboard_helper.h"
#include "sleep.h"
#include <esp_sleep.h>
#include "driver/gpio.h"
#include "driver/rtc_io.h" 
#include "OTA_handler.h"

// todo OTA updates with sleep

// Init instances
DHT dht(PIN_DHT, DHTTYPE);
WiFiClient espClient; // Initialize ThingsBoard client
ThingsBoard tb(espClient); // Initialize ThingsBoard instance
RTC_DATA_ATTR int bootCount = 0;  //counts number of boots


void setup() {
  ready_GPIO();
  Serial.begin(SERIAL_BAUD_RATE);
  dht.begin();
  WiFi.begin(WIFI_AP_NAME, WIFI_PASSWORD);
  InitWiFi();
  LED_on();
  start_OTA();

  // ++bootCount;
  // Serial.println("Boot number: " + String(bootCount));
  // print_wakeup_reason();
  // esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);
  // delay(500);
}

void loop() {
  ArduinoOTA.handle();  // Handles OTA operations
  delay(2000);

  // Get sensor values
  TempAndHumidity TandH;
  float soil_moisture;
  for (int i = 0; i < 2; i++)
  {
    TandH = get_temp_and_hum();
    soil_moisture = get_Soil(reg_b);
    delay(1000);
  }  

  check_WiFi(); // Reconnect to WiFi, if needed
  check_TB();   // Reconnect to ThingsBoard, if needed
  check_RPC_subscribe(); // Reconnect to RPC

  // Log values
  log_to_tb(TandH.temperature, TandH.humidity, soil_moisture);  // log temp, hum, soil to thingsboard

  tb.loop();  // Process messages

  // Serial.println("Going to sleep now...");
  // delay(30000);
  // Serial.flush(); 
  // esp_light_sleep_start();
}