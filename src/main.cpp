#include <Arduino.h>
#include "code.h"
#include "sensors.h"
#include "wifi_helper.h"
#include "config.h"


// Init instances
DHT dht(PIN_DHT, DHTTYPE);


void setup() {
  ready_GPIO();
  Serial.begin(SERIAL_BAUD_RATE);
  dht.begin();
  sayMyName(myName);
}

void loop() {

  get_temperature(dht);
  delay(500); // needs small delay between dht reads
  get_humidity(dht);
  get_Soil(reg_b);

  delay(3000);
}