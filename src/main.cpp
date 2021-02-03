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
  Serial.begin(SERIAL_BAUD_RATE);
  dht.begin();
  WiFi.begin(WIFI_AP_NAME, WIFI_PASSWORD);
  InitWiFi();
  sayMyName(myName);
}

void loop() {

  get_temperature(dht);
  delay(500); // needs small delay between dht reads
  get_humidity(dht);
  get_Soil(reg_b);

  delay(3000);
}