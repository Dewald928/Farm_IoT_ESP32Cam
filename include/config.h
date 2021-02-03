// Constants
#define PIN_DHT 15 // Digital pin connected to the DHT sensor
#define PIN_SOIL 14 // Analog pin for soil sensor
#define PIN_BATTERY 12 // Analog pin for battery level
#define PIN_LED 33 // Pin for onboard led
#define DHTTYPE DHT22 //DHT22 sensor
#define SERIAL_BAUD_RATE 115200 // Serial speed

// Sleep
#define uS_TO_S_FACTOR 1000000  /* Conversion factor for micro seconds to seconds */
#define TIME_TO_SLEEP  30        /* Time ESP32 will go to sleep (in seconds) */

// WiFi
#define WIFI_AP_NAME        "wlan-ap" //Wifi ssid
#define WIFI_PASSWORD       "0004edb3faee"  // WiFi password

// Thingsboard
#define TB_TOKEN    "VzQXLXW5zznguTWQYa7N"
#define TB_SERVER   "demo.thingsboard.io" // ThingsBoard server instance.