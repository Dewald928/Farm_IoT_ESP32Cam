#include <Arduino.h>
#include "code.h"
#include "sensors.h"
#include "wifi_helper.h"
#include "config.h"
#include "thingsboard_helper.h"


// Init instances
DHT dht(PIN_DHT, DHTTYPE);
WiFiClient espClient; // Initialize ThingsBoard client
ThingsBoard tb(espClient); // Initialize ThingsBoard instance



void setup() {
  ready_GPIO();
  pinMode(PIN_LED, OUTPUT);
  Serial.begin(SERIAL_BAUD_RATE);
  dht.begin();
  WiFi.begin(WIFI_AP_NAME, WIFI_PASSWORD);
  InitWiFi();
  sayMyName(myName);
  LED_on();
}

void loop() {
  delay(5000);
  
  check_WiFi(); // Reconnect to WiFi, if needed
  check_TB();   // Reconnect to ThingsBoard, if needed


  get_temperature();
  delay(600); // needs small delay between dht reads
  get_humidity();
  get_Soil(reg_b);


}