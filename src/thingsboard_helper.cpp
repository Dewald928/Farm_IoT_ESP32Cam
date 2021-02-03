#include "thingsboard_helper.h"


void check_TB(){
    if (!tb.connected()) {
    // subscribed = false; // only for sending commands

    // Connect to the ThingsBoard
    Serial.print("Connecting to: ");
    Serial.print(TB_SERVER);
    Serial.print(" with token ");
    Serial.println(TB_TOKEN);
    if (!tb.connect(TB_SERVER, TB_TOKEN)) {
      Serial.println("Failed to connect");
      return;
    }
  }
} 
