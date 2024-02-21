#include <Arduino.h>
#include <math.h>
#include "PID.h"
#include "EncoderVelocity.h"
#include "util.h"
#include "MotorDriver.h"
#include "kinematics.h"
#include "joystick.h"

// #define SerialMonitor
#define MatlabPlot

#define HORIZONTAL_LINE 0
#define VERTICAL_LINE 1
#define CIRCLE 2
#define JOYSTICK 3

unsigned long startTime;
unsigned long elapsedTime;
unsigned long setupTime = 3000;

// TODO 2: Change this trajectory_type to 
int trajectory_type = HORIZONTAL_LINE;

//PID Parameters
double tau = 0.1; //seconds
PID motorPID1(5.0, 0.0, 0.0, tau, 0.1, false);
PID motorPID2(5.0, 0.0, 0.0, tau, 0.1, false);

JoystickReading joystickReading;

JointSpace setpoint = {THETA1_OFFSET, 0.0};
JointSpace newSetpoint;
JointSpace endEffectorState;
TaskSpace endEffectorTarget;
TaskSpace endEffectorActual;

double theta1 = 0; //radians
double theta2 = 0; //radians
double controlEffort1 = 0; //duty cycle
double controlEffort2 = 0; //duty cycle

MotorDriver motor1(DIR1, PWM1, 0);
MotorDriver motor2(DIR2, PWM2, 0);
EncoderVelocity encoder1(ENCODER1_A_PIN, ENCODER1_B_PIN, CPR_60_RPM, 0.2);
EncoderVelocity encoder2(ENCODER2_A_PIN, ENCODER2_B_PIN, CPR_60_RPM, 0.2);

// Checks if provided JointSpace state is within safety limits
// Returns true if it is and false otherwise
bool safetyLimit(JointSpace state) {
    return abs(state.theta1 - M_PI/2.0) <= M_PI/2.0 &&
           abs(state.theta2) <= M_PI*0.9;
};

void setup() {
    motor1.setup();
    motor2.setup();

    Serial.begin(); 
    setupJoystick();

    startTime = millis();
}

void loop() {
    // Update setpoint at 1kHz
    EVERY_N_MICROS(1000) {
        elapsedTime = millis() - startTime;
        // Takes setupTime milliseconds to go to initial position 
        if (elapsedTime < setupTime) {
            newSetpoint = {-1.0, -1.82};

            newSetpoint.theta1 += THETA1_OFFSET;
            newSetpoint.theta2 = -newSetpoint.theta2;
        } else {
            if (trajectory_type == HORIZONTAL_LINE) {
                // Translates the setpoint to the defined coordinate system
                newSetpoint.theta1 += THETA1_OFFSET;
                newSetpoint.theta2 = -newSetpoint.theta2;
            } else if (trajectory_type == VERTICAL_LINE) {
                ;
            } else if (trajectory_type == CIRCLE) {
                ;
            } else if (trajectory_type == JOYSTICK) {
                joystickReading = readJoystick(); 
                // TODO: Convert joystickReading to a reasonable target end effector position
                // Make sure your endEffectorTarget coordinates are bounded within a reasonable range
                // e.g. x in [-25, 25], y in [20, 35]
                // endEffectorTarget.x = 
                // endEffectorTarget.y = 
            } else {
                ;
            }
        }

        // TODO: Set newSetpoint using inverseKinematics() 
        // newSetpoint = 
        
        // If new setpoint is within safety limits, use new setpoint
        // Otherwise, keeps old setpoint so robot does nothing
        if (safetyLimit(newSetpoint)) {
            setpoint = newSetpoint;
        }

        endEffectorState = {theta1, theta2};
        endEffectorActual = forwardKinematics(endEffectorState);
    }

    // Update PID at 1kHz
    EVERY_N_MICROS(1000) {        
        theta1 = encoder1.getPosition() + THETA1_OFFSET;
        theta2 = -encoder2.getPosition();
        controlEffort1 = motorPID1.calculateParallel(theta1, setpoint.theta1);
        controlEffort2 = motorPID2.calculateParallel(theta2, setpoint.theta2);

        motor1.drive(controlEffort1);
        motor2.drive(controlEffort2);
    }

    // Print values at 50Hz
    EVERY_N_MILLIS(25) {
            #ifdef SerialMonitor
            // Print values to serial monitor
                Serial.printf("Target X: %.3f, Y: %.3f   "
                          "Actual X: %.3f, Y: %.3f",
                          endEffectorTarget.x, endEffectorTarget.y,
                          endEffectorActual.x, endEffectorActual.y);
            #endif

            #ifdef MatlabPlot
                Serial.printf("%.3f\t%.3f\t%.3f\t%.3f\n", 
                endEffectorTarget.x, endEffectorTarget.y, endEffectorActual.x, endEffectorActual.y);
            #endif
    }
}
