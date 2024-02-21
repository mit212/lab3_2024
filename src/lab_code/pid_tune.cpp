#include <Arduino.h>
#include "PID.h"
#include "EncoderVelocity.h"
#include "pinout.h"
#include "util.h"
#include "MotorDriver.h"

#define Motor1
// #define Motor2

#define Constant
// #define SquareWave

// #define SerialMonitor
#define PythonPlot

//PID Parameters
double kp = 5.0;
double ki = 0;
double kd = 0;
double tau = 0.1; //seconds
PID motorPID(kp, ki, kd, 0, tau, false);

double setpoint = 0; 
double position = 0; //radians
double controlEffort = 0; //duty cycle
double desiredPosition = M_PI/4.0;

int squarePeriod = 4000;  // square wave period in milli-seconds
int squareOn = 2000; 

#ifdef Motor1
    MotorDriver motor(DIR1, PWM1, 0);
    EncoderVelocity encoder(ENCODER1_A_PIN, ENCODER1_B_PIN, CPR_60_RPM, 0.2);
#endif

#ifdef Motor2
    MotorDriver motor(DIR2, PWM2, 0);
    EncoderVelocity encoder(ENCODER2_A_PIN, ENCODER2_B_PIN, CPR_60_RPM, 0.2);
#endif


void setup() {
    motor.setup();
    Serial.begin(); 
}

void loop() {
    // Update PID at 1kHz
    EVERY_N_MICROS(1000) {
        // PID control logic
        #ifdef SquareWave
            if (millis() % squarePeriod < squareOn)   
                setpoint = desiredPosition;
            else
                setpoint = 0.0;
        #endif
        position = encoder.getPosition();
        controlEffort = motorPID.calculateParallel(position, setpoint);
        motor.drive(controlEffort);
    }

    // Print values at 40Hz
    EVERY_N_MILLIS(25) {
            // Print values to serial monitor
            #ifdef SerialMonitor
            // Print values to serial monitor
                Serial.printf("Setpoint (rad): %.2f, Position (rad): %.2f, Control Effort: %.2f",
                          setpoint, position, controlEffort);
            #endif

            #ifdef PythonPlot
                Serial.printf("%.4f\t%.3f\t%.3f\t%.3f\t%.3f\n", millis()/1000.0, setpoint, position, controlEffort, motor.getCurrentDutyCycle());
            #endif
        }
}
