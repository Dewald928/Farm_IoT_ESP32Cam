#include "thingsboard_helper.h"
// Helper macro to calculate array size
#define COUNT_OF(x) ((sizeof(x) / sizeof(0 [x])) / ((size_t)(!(sizeof(x) % sizeof(0 [x])))))

bool RPC_subscribed = false;
uint8_t leds_control[] = {PIN_FLASH, PIN_LED}; // Array with LEDs that should be controlled from ThingsBoard, one by one
// Initial period of LED cycling.
int SLEEP = 1;     // 0, doesn't sleep
int tunnelNum = 0; // Default tunnel number

void check_TB()
{
  if (!tb.connected())
  {
    // subscribed = false; // only for sending commands

    // Connect to the ThingsBoard
    Serial.print("Connecting to: ");
    Serial.print(TB_SERVER);
    Serial.print(" with token ");
    Serial.println(TB_TOKEN);
    if (!tb.connect(TB_SERVER, TB_TOKEN))
    {
      Serial.println("Failed to connect");
      return;
    }
  }
}

// Processes function for RPC call "setValue"
// RPC_Data is a JSON variant, that can be queried using operator[]
// See https://arduinojson.org/v5/api/jsonvariant/subscript/ for more details
RPC_Response processSetSLEEP(const RPC_Data &data)
{
  Serial.println("Received the set SLEEP method");

  // Process data

  SLEEP = data;

  Serial.print("Set new delay: ");
  Serial.println(SLEEP);

  return RPC_Response(NULL, SLEEP);
}

// Processes function for RPC call "getValue"
// RPC_Data is a JSON variant, that can be queried using operator[]
// See https://arduinojson.org/v5/api/jsonvariant/subscript/ for more details
RPC_Response processGetSLEEP(const RPC_Data &data)
{
  Serial.println("Received the get SLEEP method");

  return RPC_Response(NULL, SLEEP);
}

RPC_Response processSetFlash(const RPC_Data &data)
{
  Serial.println("Received the set flash RPC method");
  int enabled = data;

  Serial.print(" to state ");
  Serial.println(enabled);

  // Process data
  digitalWrite(PIN_FLASH, enabled);

  return RPC_Response(NULL, enabled);
}

RPC_Response processGetFlash(const RPC_Data &data)
{
  Serial.println("Check flash status");
  int flash_status = digitalRead(PIN_FLASH);

  return RPC_Response(NULL, flash_status);
}

// Gets tunnel number
RPC_Response processGetTunnelNum(const RPC_Data &data)
{
  Serial.println("Getting tunnel number: ");
  tunnelNum = data;
  Serial.print(tunnelNum);

  return RPC_Response(NULL, tunnelNum);
}

// Processes function for RPC call "setGpioStatus"
// RPC_Data is a JSON variant, that can be queried using operator[]
// See https://arduinojson.org/v5/api/jsonvariant/subscript/ for more details
RPC_Response processSetGpioState(const RPC_Data &data)
{
  Serial.println("Received the set GPIO RPC method");

  int pin = data["pin"];
  bool enabled = data["enabled"];

  if (pin < COUNT_OF(leds_control))
  {
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
    {"setSLEEP", processSetSLEEP},
    {"getSLEEP", processGetSLEEP},
    {"setGpioStatus", processSetGpioState},
    {"getTunnelNum", processGetTunnelNum},
    // { "setFlash",       processSetFlash},
    // { "getFlash",       processGetFlash},
};

void check_RPC_subscribe()
{
  // Subscribe for RPC, if needed
  if (!RPC_subscribed)
  {
    Serial.println("Subscribing for RPC...");

    // Perform a subscription. All consequent data processing will happen in
    // callbacks as denoted by callbacks[] array.
    if (!tb.RPC_Subscribe(callbacks, COUNT_OF(callbacks)))
    {
      Serial.println("Failed to subscribe for RPC");
      return;
    }

    Serial.println("Subscribe done");
    RPC_subscribed = true;
  }
}

void log_to_tb(float temperature, float humidity, float soil_moisture, float battery_voltage)
{
  tb.sendTelemetryFloat("temperature", temperature);
  tb.sendTelemetryFloat("humidity", humidity);
  tb.sendTelemetryFloat("soil_moisture", soil_moisture);
  tb.sendTelemetryFloat("battery_voltage", battery_voltage);
}

void log_attributes_tb(String ip_address, String firmware_version)
{
  Serial.println("Logging attributes");
  Serial.println(ip_address);
  tb.sendAttributeString("IP", ip_address.c_str());
  tb.sendAttributeString("Firmware", firmware_version.c_str());
}
