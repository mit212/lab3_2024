#include <Arduino.h>
#include "pinout.h"
#include "potentiometer.h"

PotReading pot;

void setup() {
    Serial.begin();

    setupPot();
}

void loop() {
    pot = readPot();
    Serial.printf("Reading: %d\n", pot);
    
    delay(50);
}
