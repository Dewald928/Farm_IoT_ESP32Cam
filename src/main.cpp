#include <Arduino.h>
#include "code.h"
#include "sensors.h"


void setup() {
  ready_GPIO();
  Serial.begin(115200);
  sayMyName(myName);
}

void loop() {

  get_Soil(14, reg_b);

  delay(2000);
}