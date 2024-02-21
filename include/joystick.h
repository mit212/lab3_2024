#ifndef JOYSTICK
#define JOYSTICK

#include "pinout.h"

struct JoystickReading {
    double x;
    double y;
};

void setupJoystick();
JoystickReading readJoystick();

#endif