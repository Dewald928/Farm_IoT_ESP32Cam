// Read temp and hum
// Read soil and battery
// Control led and flash
#include "sensors.h"

uint64_t reg_b;

void ready_GPIO(){
    reg_b = READ_PERI_REG(SENS_SAR_READ_CTRL2_REG);
}


float get_Soil(int PIN_Soil, uint64_t reg_b){
    // ADC Pin Reset: Do this before every analogRead()
    WRITE_PERI_REG(SENS_SAR_READ_CTRL2_REG, reg_b);
    //VERY IMPORTANT: DO THIS TO NOT HAVE INVERTED VALUES! port 14 inverts but not 12. weird.
    SET_PERI_REG_MASK(SENS_SAR_READ_CTRL2_REG, SENS_SAR2_DATA_INV);

    int value = analogRead(PIN_Soil);
    Serial.println(value);
    return value;
}