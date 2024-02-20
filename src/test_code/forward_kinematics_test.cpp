#include "EncoderVelocity.h"
#include "pinout.h"
#include "EveryNMillis.h"
#include "kinematics.h"

#define PRINT_DELAY 30 // Delay between printing to serial in milliseconds

JointSpace state;
TaskSpace point;

// Encoder velocity readers
EncoderVelocity encoder1(ENCODER1_A_PIN, ENCODER1_B_PIN, CPR_60_RPM);
EncoderVelocity encoder2(ENCODER2_A_PIN, ENCODER2_B_PIN, CPR_60_RPM);

void setup() {
    Serial.begin();
}

// Prints the equivalent task space coordinates to the serial monitor
void printExpectedCartesian(){
    state.theta1 = encoder1.getPosition();
    state.theta2 = encoder2.getPosition();
    point = forwardKinematics(state);

    Serial.printf("x: %.2f, y: %.2f\n", point.x, point.y);
 }

void loop(){
    // Print every PRINT_DELAY milliseconds
    EVERY_N_MILLIS(PRINT_DELAY) {
        printExpectedCartesian();
    }
}