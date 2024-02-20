#include "pinout.h"

struct JoystickReading {
    int x;
    int y;
};

void setupJoystick();
JoystickReading readJoystick();
