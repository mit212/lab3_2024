#include <Arduino.h>
#include "PID.h"
#include "EncoderVelocity.h"
#include "pinout.h"
#include "util.h"
#include "MotorDriver.h"

// Switch between printing in the Serial Monitor 
// and streaming to Python for plotting.
// Comment out at least one of the two lines below.
// #define SerialMonitor
#define PythonPlot

//PID Parameters
double kp = 5;
double ki = 0;
double kd = 0;
double tau = 0.1; //seconds
PID motorPID(kp, ki, kd, 0, tau, false);

double setpoint = 1.5; //radians per second
double filt_velocity = 0; //radians per second
double position = 0; //radians per second

double controlEffort = 0; //duty cycle

MotorDriver motor(DIR1, PWM1, 0);
EncoderVelocity encoder(ENCODER_A_PIN, ENCODER_B_PIN, CPR_60_RPM, 0.2);

//variables for calculating the average time between PID loops
unsigned long currentPidLoopStartTime = 0;
unsigned long previousPidLoopStartTime = 0;
unsigned long timeBetweenPidLoopsAccumulator = 0;
int pidLoopIntervalCount = 0;

double alpha = 0.5;

void setup() {
    motor.setup();
    Serial.begin(); 
    previousPidLoopStartTime = micros(); // Record start time of first PID loop
}

void loop() {
    // Update PID at 10kHz
    EVERY_N_MICROS(100) {
        currentPidLoopStartTime = micros(); // Record start time of current PID loop

        // Calculate the time between the start of the current and the previous PID loop
        if (pidLoopIntervalCount > 0) { // Skip the first loop to have a previous time to compare
            timeBetweenPidLoopsAccumulator += currentPidLoopStartTime - previousPidLoopStartTime;
        }
        previousPidLoopStartTime = currentPidLoopStartTime; // Update previous start time for the next loop
        pidLoopIntervalCount++;

        // PID control logic
        //filt_velocity = alpha * encoder.getVelocity() + (1 - alpha) * filt_velocity; // Alpha-based low-pass filter 
        position = encoder.getPosition();
        controlEffort = motorPID.calculateParallel(setpoint, position);
        motor.drive(controlEffort);
    }

    // Print values at 10Hz
    EVERY_N_MILLIS(100) {
        if (pidLoopIntervalCount > 1) { // Ensure there's at least one interval to calculate
            // Calculate the average time between PID loop starts
            double averageTimeBetweenPidLoops = (double)timeBetweenPidLoopsAccumulator / (pidLoopIntervalCount - 1);
            
            #ifdef SerialMonitor
            // Print values to serial monitor
            Serial.printf("Setpoint (rad/s): %.2f, Filtered Velocity (rad/s): %.2f, Control Effort: %.2f, Avg Time Between PID Loops (us): %.2f\n",
                          setpoint, filt_velocity, controlEffort, averageTimeBetweenPidLoops);
            #endif

            #ifdef PythonPlot
            Serial.printf("%.6f,%.6f,%.6f\n", setpoint, position, controlEffort);
            #endif

            // Reset the accumulator and count for the next set of averages
            timeBetweenPidLoopsAccumulator = 0;
            pidLoopIntervalCount = 1; // Reset to 1 to skip the first loop's interval calculation
        }
    }
}
