#include <Arduino.h>
#include "code.h"
#include "sensors.h"
#include "wifi_helper.h"

// Constants
#define PIN_DHT 15 // Digital pin connected to the DHT sensor
#define PIN_SOIL 14 // Analog pin for soil sensor
#define PIN_BATTERY 12 // Analog pin for battery level
#define PIN_LED 33 // Pin for onboard led
#define DHTTYPE DHT22 //DHT22 sensor
#define SERIAL_BAUD_RATE 115200 // Serial speed
#define SLEEP_TIME 60000 // 60 seconds?

// WiFi
#define WIFI_AP_NAME        "wlan-ap" //Wifi ssid
#define WIFI_PASSWORD       "0004edb3faee"  // WiFi password

// Thingsboard
#define TB_TOKEN    "VzQXLXW5zznguTWQYa7N"
#define TB_SERVER   "demo.thingsboard.io" // ThingsBoard server instance.

// Init instances
DHT dht(PIN_DHT, DHTTYPE);


void setup() {
  ready_GPIO();
  Serial.begin(SERIAL_BAUD_RATE);
  dht.begin();
  sayMyName(myName);
}

void loop() {

  get_temperature(dht, PIN_DHT);
  delay(500); // needs small delay
  get_humidity(dht, PIN_DHT);
  get_Soil(14, reg_b);

  delay(3000);
}