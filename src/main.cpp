#include <Arduino.h>
#include "sensors.h"
#include "wifi_helper.h"
#include "config.h"
#include "thingsboard_helper.h"
#include "sleep.h"
#include <esp_sleep.h>
#include "driver/gpio.h"
#include "driver/rtc_io.h"
#include "OTA_handler.h"
// #include "telegramcamera.h"
#include "camera_post.h"
#include "esp_bt.h"
#include <NTPClient.h>
#include <WiFiUdp.h>

// Init instances
DHT dht(PIN_DHT, DHTTYPE);
WiFiClient espClient;            // Initialize ThingsBoard client
ThingsBoard tb(espClient);       // Initialize ThingsBoard instance
RTC_DATA_ATTR int bootCount = 0; //counts number of boots
int loop_count = 0;              //counts number of main loops
WiFiUDP ntpUDP;                  // get date-time from wifi
NTPClient timeClient(ntpUDP);     

void setup()
{
  ready_GPIO();
  Serial.begin(SERIAL_BAUD_RATE);
  dht.begin();
  WiFi.begin(WIFI_AP_NAME, WIFI_PASSWORD);
  InitWiFi();
  check_TB(); // Reconnect to ThingsBoard, if needed
  log_attributes_tb(WiFi.localIP().toString(), FIRMWARE_VERSION);
  get_tunnelNum();
  LED_on();
  start_OTA();
  // configInitCamera();
  InitCamera();
  timeClient.begin();

  ++bootCount;
  Serial.println("boot number: " + String(bootCount));
  print_wakeup_reason();
  esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);
  delay(500);
}

void loop()
{
  timeClient.update();  // gets current date-time
  ArduinoOTA.handle(); // Handles OTA operations
  // checkTelegram();
  // delay(1000);
  Serial.print("Loop count:");
  Serial.println(loop_count);

  // Switch off wifi and bluetooth before taking readings
  WiFi.disconnect();
  WiFi.mode(WIFI_OFF);
  btStop();

  // Get sensor values
  TempAndHumidity TandH;
  float soil_moisture;
  float battery_voltage;
  for (int i = 0; i < 2; i++)
  {
    Serial.print("Measuring count:");
    Serial.println(i);
    TandH = get_temp_and_hum();
    soil_moisture = get_Soil(reg_b);
    battery_voltage = get_battery_voltage(reg_b);
    delay(1000);
  }

  check_WiFi();          // Reconnect to WiFi, if needed
  check_TB();            // Reconnect to ThingsBoard, if needed
  check_RPC_subscribe(); // Reconnect to RPC

  // Log values
  log_to_tb(TandH.temperature, TandH.humidity, soil_moisture, battery_voltage); // log temp, hum, soil to thingsboard

  tb.loop(); // Process messages

  if (loop_count >= 2)
  {
    // if night time. don't take picture
    int currentHour = timeClient.getHours();
    if (currentHour < 17 && currentHour > 4) //UTC time
    {
      sendPhoto();
    }   
    loop_count = 0;
    RPC_subscribed = false; //resubscribe after sleeping. Move moaybe?
    check_OTA(SLEEP);       //if OTA don't sleep
  }

  loop_count++;
  ArduinoOTA.handle();
}