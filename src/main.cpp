#include <Arduino.h>
#include "code.h"
#include "sensors.h"
#include "wifi_helper.h"
#include "config.h"
#include "thingsboard_helper.h"
#include "sleep.h"

// todo OTA updates

// Init instances
DHT dht(PIN_DHT, DHTTYPE);
WiFiClient espClient; // Initialize ThingsBoard client
ThingsBoard tb(espClient); // Initialize ThingsBoard instance
RTC_DATA_ATTR int bootCount = 0;  //counts number of boots


void setup() {
  ready_GPIO();
  pinMode(PIN_LED, OUTPUT);
  Serial.begin(SERIAL_BAUD_RATE);
  dht.begin();
  WiFi.begin(WIFI_AP_NAME, WIFI_PASSWORD);
  InitWiFi();
  sayMyName(myName);
  LED_on();

  ++bootCount;
  Serial.println("Boot number: " + String(bootCount));
  print_wakeup_reason();
  esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);
}

void loop() {
  // delay(10000);
  
  check_WiFi(); // Reconnect to WiFi, if needed
  check_TB();   // Reconnect to ThingsBoard, if needed

  TempAndHumidity TandH = get_temp_and_hum();
  float soil_moisture = get_Soil(reg_b);

  log_to_tb(TandH.temperature, TandH.humidity, soil_moisture);  // log temp, hum, soil to thingsboard

  tb.loop();  // Process messages

  Serial.println("Going to sleep now");
  Serial.flush(); 
  esp_deep_sleep_start();
}