#include "thingsboard_helper.h"
// Helper macro to calculate array size
#define COUNT_OF(x) ((sizeof(x)/sizeof(0[x])) / ((size_t)(!(sizeof(x) % sizeof(0[x])))))

bool RPC_subscribed = false;
uint8_t leds_control[] = { PIN_FLASH, PIN_LED}; // Array with LEDs that should be controlled from ThingsBoard, one by one
// Initial period of LED cycling.
int led_delay = 1000;

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


// Processes function for RPC call "setValue"
// RPC_Data is a JSON variant, that can be queried using operator[]
// See https://arduinojson.org/v5/api/jsonvariant/subscript/ for more details
RPC_Response processDelayChange(const RPC_Data &data)
{
  Serial.println("Received the set delay RPC method");

  // Process data

  led_delay = data;

  Serial.print("Set new delay: ");
  Serial.println(led_delay);

  return RPC_Response(NULL, led_delay);
}

// Processes function for RPC call "getValue"
// RPC_Data is a JSON variant, that can be queried using operator[]
// See https://arduinojson.org/v5/api/jsonvariant/subscript/ for more details
RPC_Response processGetDelay(const RPC_Data &data)
{
  Serial.println("Received the get value method");

  return RPC_Response(NULL, led_delay);
}

// Processes function for RPC call "setGpioStatus"
// RPC_Data is a JSON variant, that can be queried using operator[]
// See https://arduinojson.org/v5/api/jsonvariant/subscript/ for more details
RPC_Response processSetGpioState(const RPC_Data &data)
{
  Serial.println("Received the set GPIO RPC method");

  int pin = data["pin"];
  bool enabled = data["enabled"];

  if (pin < COUNT_OF(leds_control)) {
    Serial.print("Setting LED ");
    Serial.print(pin);
    Serial.print(" to state ");
    Serial.println(enabled);

    digitalWrite(leds_control[pin], enabled);
  }

  return RPC_Response(data["pin"], (bool)data["enabled"]);
}


// RPC handlers
RPC_Callback callbacks[] = {
  { "setValue",         processDelayChange },
  { "getValue",         processGetDelay },
  { "setGpioStatus",    processSetGpioState },
};


void check_RPC_subscribe(){
  // Subscribe for RPC, if needed
  if (!RPC_subscribed) {
    Serial.println("Subscribing for RPC...");

    // Perform a subscription. All consequent data processing will happen in
    // callbacks as denoted by callbacks[] array.
    if (!tb.RPC_Subscribe(callbacks, COUNT_OF(callbacks))) {
      Serial.println("Failed to subscribe for RPC");
      return;
    }

    Serial.println("Subscribe done");
    RPC_subscribed = true;
  }
}