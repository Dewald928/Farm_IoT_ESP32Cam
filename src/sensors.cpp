// Read temp and hum
// Read soil and battery
// Control led and flash
#include "sensors.h"

uint64_t reg_b;

void ready_GPIO(){
    WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0); 
    reg_b = READ_PERI_REG(SENS_SAR_READ_CTRL2_REG);
    pinMode(PIN_LED, OUTPUT);
    // pinMode(PIN_FLASH, OUTPUT);
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
    // delay(1000);
    // value = analogRead(PIN_SOIL);   // needs to take 2nd reading
    float soil_moisture = map(value, 2635, 1050, 0, 100);
    if (soil_moisture < 0) { soil_moisture = 0;} // negative moisture to zero
    Serial.print(F("Moisture: "));
    Serial.print(soil_moisture);
    Serial.println('%');
    return soil_moisture;
}


float get_temperature() {
    float t = dht.readTemperature(); // Read temperature as Celsius (the default)
    // delay(500);
    // t = dht.readTemperature();
    // Check if any reads failed and exit early (to try again).
    if (isnan(t)) {
        Serial.println(F("Failed to read from DHT sensor!"));
        delay(1000);
    }
    Serial.print(F("Temperature: "));
    Serial.print(t);
    Serial.println(F("°C "));

    return t;
} 


float get_humidity() {
    float h = dht.readHumidity(); // Read humidity
    // delay(500);
    // h = dht.readHumidity();

    // Check if any reads failed and exit early (to try again).
    if (isnan(h)) {
        Serial.println(F("Failed to read from DHT sensor!"));
        delay(1000);
    }
    Serial.print(F("Humidity: "));
    Serial.print(h);
    Serial.println(F("%"));

    return h;
} 


TempAndHumidity get_temp_and_hum(){
    TempAndHumidity values;
    float h = dht.readHumidity();
    float t = dht.readTemperature();
    delay(1000);
    h = dht.readHumidity();
    t = dht.readTemperature();

    if (isnan(h) || isnan(t)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    }

    Serial.print(F("Temperature: "));
    Serial.print(t);
    Serial.println(F("°C "));
    Serial.print(F("Humidity: "));
    Serial.print(h);
    Serial.println(F("%"));

    values.temperature = t;
	values.humidity = h;
    return values;
}


float get_battery_voltage(uint64_t reg_b){
    // ADC Pin Reset: Do this before every analogRead()
    WRITE_PERI_REG(SENS_SAR_READ_CTRL2_REG, reg_b);
    //VERY IMPORTANT: DO THIS TO NOT HAVE INVERTED VALUES! port 14 inverts but not 12. weird.
    SET_PERI_REG_MASK(SENS_SAR_READ_CTRL2_REG, SENS_SAR2_DATA_INV);

    int value = analogRead(PIN_BATTERY);
    float battery_voltage = mapf(value, 4435, 0, 4.2, 0);
    // float battery_voltage = (value * 4.2)/4095;

    Serial.print(F("Battery voltage: "));
    Serial.print(value);
    Serial.print(' ');
    Serial.print(battery_voltage);
    Serial.println('V');

    return battery_voltage;
}

float mapf(float val, float in_min, float in_max, float out_min, float out_max) {
    return (val - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}


