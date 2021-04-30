//Software
#define FIRMWARE_VERSION "0.0.3"

// Constants
#define PIN_DHT 15 // Digital pin connected to the DHT sensor
#define PIN_SOIL 14 // Analog pin for soil sensor
#define PIN_BATTERY 2 // Analog pin for battery level
#define PIN_LED 33 // Pin for onboard led
#define PIN_FLASH 4 // Pin for builtin flash
#define DHTTYPE DHT22 //DHT22 sensor
#define SERIAL_BAUD_RATE 115200 // Serial speed

// Sleep
#define uS_TO_S_FACTOR 1000000  /* Conversion factor for micro seconds to seconds */
#define TIME_TO_SLEEP  120        /* Time ESP32 will go to sleep (in seconds) */

// WiFi
#define WIFI_AP_NAME        "wlan-ap" //Wifi ssid
#define WIFI_PASSWORD       "0004edb3faee"  // WiFi password

// Thingsboard
#define TB_TOKEN    "ZXkepFTduyZlE2oR9OnO"
#define TB_SERVER   "enginosoft.com" // ThingsBoard server instance.

// Image server
#define SERVER_ADDRESS "enginosoft.com"
#define SERVER_PORT 12345

// Telegram
#define BOT_TOKEN "1693008485:AAGTZs6P6PmW0i2_HEtSWftkzYCr3iPvOPQ"   // Initialize Telegram BOT
#define TELEGRAM_CHAT_ID  "1349347798" // Use @myidbot to find out the chat ID of an individual or a group
// Also note that you need to click "start" on a bot before it can
// message you