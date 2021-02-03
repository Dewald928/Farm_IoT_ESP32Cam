#include <Arduino.h>
#include "code.h"
#include "sensors.h"

// Constants
#define PIN_DHT 15 // Digital pin connected to the DHT sensor
#define PIN_SOIL 14 // Analog pin for soil sensor
#define PIN_BATTERY 12 // Analog pin for battery level
#define PIN_LED 33 // Pin for onboard led
#define DHTTYPE DHT22 //DHT22 sensor
#define SERIAL_BAUD_RATE 115200 // Serial speed


// Init instances
DHT dht(PIN_DHT, DHTTYPE);


void setup() {
  ready_GPIO();
  Serial.begin(SERIAL_BAUD_RATE);
  dht.begin();
  sayMyName(myName);
}

void loop() {
  delay(2000);

  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.println(F("°C "));

  get_Soil(14, reg_b);

  delay(3000);
}