#include "joystick.h"
#include <Arduino.h>

void setupJoystick() {
    pinMode(XPIN, INPUT); 
    pinMode(YPIN, INPUT); 
};

JoystickReading readJoystick() {
    JoystickReading output;
    
    output.x = analogRead(XPIN); 
    output.y = analogRead(YPIN); 

    return output;
};



