#ifndef JOYSTICK
#define JOYSTICK

#include "pinout.h"

struct JoystickReading {
    // TODO: Define your struct here.
    // The members of the struct should be in the range [-1, 1).
};

void setupJoystick();
JoystickReading readJoystick();

#endif