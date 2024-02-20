#include "EncoderVelocity.h"
#include "pinout.h"
#include "EveryNMillis.h"
#include "kinematics.h"

#define PRINT_DELAY 30 // Delay between printing to serial in milliseconds

JointSpace state;
JointSpace test_state;

// Encoder velocity readers
EncoderVelocity encoder1(ENCODER1_A_PIN, ENCODER1_B_PIN, CPR_60_RPM);
EncoderVelocity encoder2(ENCODER2_A_PIN, ENCODER2_B_PIN, CPR_60_RPM);

void setup() {
    Serial.begin();
}

//Prints the encoder readings to the serial monitor
void printExpectedJoint(){
    state.theta1 = encoder1.getPosition();
    state.theta2 = encoder2.getPosition();
    test_state = inverseKinematics(forwardKinematics(state));
    Serial.printf("theta1_error: %.2f, theta2_error: %.2f\n", 
                  abs(state.theta1 - test_state.theta1),
                  abs(state.theta2 - test_state.theta2));
 }

void loop(){
    // Print encoder readings every PRINT_DELAY milliseconds
    EVERY_N_MILLIS(PRINT_DELAY) {
        printExpectedJoint();
    }
}