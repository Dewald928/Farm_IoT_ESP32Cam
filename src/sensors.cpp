// Read temp and hum
// Read soil and battery
// Control led and flash
#include "sensors.h"

uint64_t reg_b;

void ready_GPIO(){
    reg_b = READ_PERI_REG(SENS_SAR_READ_CTRL2_REG);
}


void LED_on(){
    digitalWrite(PIN_LED, LOW);
}


void LED_off(){
    digitalWrite(PIN_LED, HIGH);
}


float get_Soil(uint64_t reg_b){
    // ADC Pin Reset: Do this before every analogRead()
    WRITE_PERI_REG(SENS_SAR_READ_CTRL2_REG, reg_b);
    //VERY IMPORTANT: DO THIS TO NOT HAVE INVERTED VALUES! port 14 inverts but not 12. weird.
    SET_PERI_REG_MASK(SENS_SAR_READ_CTRL2_REG, SENS_SAR2_DATA_INV);

    int value = analogRead(PIN_SOIL);
    float soil_moisture = map(value, 2635, 1050, 0, 100);
    Serial.print(F("Moisture: ")); // todo if soil -50% check
    Serial.print(soil_moisture);
    Serial.println('%');
    return soil_moisture;
}


float get_temperature() {
    float t = dht.readTemperature(); // Read temperature as Celsius (the default)

    // Check if any reads failed and exit early (to try again).
    if (isnan(t)) {
        Serial.println(F("Failed to read from DHT sensor!"));
        get_temperature();
        delay(1000);
    }
    Serial.print(F("Temperature: "));
    Serial.print(t);
    Serial.println(F("°C "));

    return t;
} 


float get_humidity() {
    float h = dht.readHumidity(); // Read humidity

    // Check if any reads failed and exit early (to try again).
    if (isnan(h)) {
        Serial.println(F("Failed to read from DHT sensor!"));
        get_humidity();
        delay(1000);
    }
    Serial.print(F("Humidity: "));
    Serial.print(h);
    Serial.println(F("%"));

    return h;
} 


void log_to_tb(float, float, float){

}
