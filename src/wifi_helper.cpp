#include "wifi_helper.h"

int wifi_status = WL_IDLE_STATUS;

void InitWiFi()
{
  Serial.println("Connecting to AP ...");
  // attempt to connect to WiFi network

  // Loop until we're reconnected
  int timeout_tries = 10;
  if (WiFi.status() != WL_CONNECTED)
  {
    WiFi.begin(WIFI_AP_NAME, WIFI_PASSWORD);
    int i = 0;
    while ((WiFi.status() != WL_CONNECTED) && (i < timeout_tries))
    {
      delay(500);
      Serial.print(".");
      i++;
    }
    Serial.println("Connected to AP");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
  }
}

void reconnect()
{
  // Loop until we're reconnected
  int timeout_tries = 10;
  if (WiFi.status() != WL_CONNECTED)
  {
    WiFi.begin(WIFI_AP_NAME, WIFI_PASSWORD);
    int i = 0;
    while ((WiFi.status() != WL_CONNECTED) && (i < timeout_tries))
    {
      delay(500);
      Serial.print(".");
      i++;
    }
    Serial.println("Connected to AP");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
  }
}

void check_WiFi()
{
  // Reconnect to WiFi, if needed
  if (WiFi.status() != WL_CONNECTED)
  {
    reconnect();
  }
}