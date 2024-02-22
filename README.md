# Lab 3: 2-DoF Robot Pt.2

2.12/2.120 Intro to Robotics  
Spring 2024[^1]

- [1 Validate Hardware Setup](#1-validate-hardware-setup)
  - [1.1 Validate Microcontroller](#11-validate-microcontroller)
  - [1.2 Validate Motors](#12-validate-motors)
  - [1.3 Validate Encoders](#13-validate-encoders)
  - [1.4 Validate Joystick](#14-validate-joystick)
- [2 Validate Serial Read](#2-validate-serial-read)
- [3 Step Response in Joint Space](#3-step-response-in-joint-space)
  - [3.1 Straight Arm](#31-straight-arm)
  - [3.2 Bent Elbow](#32-bent-elbow)
- [4 Forward Kinematics](#4-forward-kinematics)
- [5 Inverse Kinematics](#5-inverse-kinematics)
- [6 Cartesian Space](#6-cartesian-space)
  - [6.1 Horizontal Line](#61-horizontal-line)
  - [6.2 Vertical](#62-vertical)
  - [6.3 Joystick](#63-joystick)
- [7 Feedback Form](#7-feedback-form)
- [X Optional](#x-optional)

## 1 Validate Hardware Setup
Estimated time of completion: 10 min

Before beginning any work with hardware, it's important to make sure all of it works! Faulty wiring or hardware is often a simple bug, but can be very difficult to find with a lot of moving parts in software.

### 1.1 Validate Microcontroller

**Make sure that motor power is turned off any time you are uploading code to your microcontroller.** The arm has a tendency to spin around and hit itself if motor power is on during upload. 

Clone this repository and run `robot/blink_test.cpp`. You should see the onboard LED change colors! 

### 1.2 Validate Motors

Orient the arm so that it points straight up (+y direction) in full extension. This should always be the starting position of the arm.  

Then, run `test_code/motor_drive_test.cpp` to validate your motor setup. You can turn on motor power after clicking `RST`. You should see both motors oscillating back and forth. Remember that motor 1 is attached to the base (acts like a shoulder), and motor 2 is attached to the second link (acts like an elbow). 

As a reminder, motor power should only be on when you expect the motor to move, such as in this section. Otherwise, please keep motor power off. The yellow LED on the motor driver indicates whether motor power is on or off.

### 1.3 Validate Encoders
Run `test_code/encoder_test.cpp` to validate your encoder setup. Remember to open the Serial Monitor to see the output. Make sure that both the direction and the magnitude make sense!

### 1.4 Validate Joystick
Run `lab_code/joystick.cpp` and `test_code/joystick_test.cpp` to validate your joystick setup. You should be able to see joystick readings within the range `[-1, 1]`.

## 2 Validate Serial Read
Estimated time of completion: 10 min

In order to visualize data, we need to plot it in MATLAB. To verify that the interface between the microcontroller and MATLAB works, we will plot the outputs of `test_code/encoder_test.cpp`.

1. Open `test_code/encoder_test.cpp`. Comment out `#define SerialMonitor` and uncomment `#define MatlabPlot`. This reformats the prints in the Serial Monitor to be readable by MATLAB.
2. Run `test_code/encoder_test.cpp`, but this time, **don't open the Serial Monitor**. If you already have it open, close it by clicking the delete icon.
3. Find your microcontroller port by clicking the plug icon with the word "Auto" next to it at the bottom of the screen. The port name should be similar to `COM10` in Windows or `/dev/cu.usbmodem144101` in MacOS.
4. Open `src/matlab/SerialTest.m` in MATLAB.
5. Change the port name in `s1 = serialport(...)` (lines 28-29).
6. Run `src/matlab/SerialTest.m`. You should see four lines representing encoder positions and velocities. Feel free to rotate the links to verify that the values change accordingly.

## 3 Step Response in Joint Space
Estimated time of completion: 20 min

### 3.1 Straight Arm
Set the arm to be straight up in default position:

<p align="center">
<img src="./.images/straight_arm.png" alt="drawing" width="300"/>
</p>

Then, run `lab_code/step_response.cpp` and set the power supply voltage to around `10V`. The arm should oscillate between `theta1 = 0` and `theta1 = M_PI/4`.

To examine the step response in more detail, run `matlab/StepResponsePlot.m` in MATLAB. Make sure to change the port name (lines 27-28) before running as needed. If your controller is properly tuned (which it should be already!), the step response should have minimal overshoot, oscillations, and steady state error. 

Hit the STOP button on MATLAB after collecting some data and take a screenshot of the plot. 

### 3.2 Bent Elbow
Set the arm to be bent 90 degrees to the left at the elbow:

<p align="center">
<img src="./.images/bent_arm.png" alt="drawing" width="300"/>
</p>

Then, run `lab_code/step_response.cpp` and `matlab/StepResponsePlot.m` in MATLAB again. *Note: This is the only time we want the arm not to be in default starting position.* 

Hit the STOP button on MATLAB after collecting some data and take a screenshot of the plot. 

| :white_check_mark: CHECKOFF 1 :white_check_mark:   |
|:---------------------------------------------------|
| Show a TA or LA the screenshots of your plots. Identify and explain any differences in the step response between the straight arm and bent arm configurations. |

## 4 Forward Kinematics
Estimated time of completion: 10 min

First, derive the forward kinematic equations for a 2-DoF arm. In other words, derive equations for `x` and `y` in terms of <code>Θ<sub>1</sub></code> and <code>Θ<sub>2</sub></code>.

To validate your derived equations, first move your robotic arm to the angles `(pi/2, 0)` (pointing straight forward). Then, run `lab_code/kinematics.cpp` and `test_code/forward_kinematics_test.cpp`. You should see the Serial Monitor printing the `x` and `y` real-life coordinates of the marker holder in centimeters (e.g. at the angle `(pi/2, 0)`, `x=0` and `y~=38`).

## 5 Inverse Kinematics
Estimated time of completion: 10 min

Using the forward kinematic equations you found, derive the inverse kinematic equations for a 2-DoF arm. In other words, derive equations for <code>Θ<sub>1</sub></code> and <code>Θ<sub>2</sub></code> in terms of `x` and `y`.

Add inverse kinematics equations

<details>
<summary><i> What is inverse kinematics? </i></summary>

It's the opposite of forward kinematics!
Put simply, forward inverse kinematics answers the question, "Given the desired x,y coordinates of the robot's hand, what should the angles of the robot's joints be?" For more, refer to lecture 2!

</details>

Then, translate your derived equations into code by completing the `TODO 2`s in `kinematics.cpp`.

To validate your derived equations, run `lab_code/kinematics.cpp` and `test_code/inverse_kinematics_test.cpp`. You should see `theta1_error` and `theta2_error` be 0.

## 6 Cartesian Space
Estimated time of completion: 10 min

Now that we tuned our PID controller and implemented inverse kinematics, we can follow any trajectory we want in Cartesian space!

### 6.1 Horizontal Line
Set the setpoint to be a horizontal line in Cartesian space.

### 6.2 Vertical 
Set the setpoint to be a vertical line in Cartesian space.

### 6.3 Joystick
Set the setpoint to be the reading from your joystick.

| :white_check_mark: CHECKOFF X :white_check_mark:   |
|:---------------------------------------------------|
| Demonstrate the arm following your joystick. |

## 7 Feedback Form

Before you leave, please fill out https://tinyurl.com/212-feedback. 

| :white_check_mark: CHECKOFF X :white_check_mark:   |
|:---------------------------------------------------|
| Show the feedback form completion screen to a TA or LA. |

## X Optional

Here are some optional challenges you can try if you finish lab early!
1. Modify `lab_code/drawing.cpp` to create a fun, unique trajectory.
2. Modify `test_code/inverse_kinematics_test.cpp` so that the errors are always `0` regardless of elbow-up or elbow-down configuration. 
3. Tune the PID gains of both motors.

[^1]: Version 1 - 2024: Jinger Chong, Josh Sohn
