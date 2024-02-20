#include <Arduino.h>
#include "pinout.h"

double X = 0;
double Y = 0;

void setup() {
    Serial.begin();

    pinMode(XPIN, INPUT);
    pinMode(YPIN, INPUT);
}

void loop() {
    X = analogRead(XPIN)/2048.0 - 1.0;
    Y = analogRead(YPIN)/2048.0 - 1.0;
    Serial.printf("%.4f,%.4f,%.4f,0\n", millis()/1000.0, X, Y);
    
    delay(100);
}
