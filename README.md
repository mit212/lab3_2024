# Lab 2: 2-DoF Robot Pt.1

2.12/2.120 Intro to Robotics  
Spring 2024[^1]

- [1 Validate Hardware Setup](#1-validate-hardware-setup)
  - [1.1 Validate Encoders](#11-validate-encoders)
  - [1.2 Validate Motors](#12-validate-motors)
  - [1.3 Validate Joystick](#13-validate-joystick)
- [2 Potentiometers](#2-potentiometers)
  - [2.1 Wire Potentiometers](#21-wire-potentiometers)
  - [2.2 Read Potentiometers](#22-read-potentiometers)
- [3 Forward Kinematics](#3-forward-kinematics)
- [4 Validate Serial Read](#4-validate-serial-read)
- [5 Tune PID Using Potentiometers](#5-tune-pid-using-potentiometers)
  - [](#)
- [3 Feedback Form](#3-feedback-form)

## 1 Validate Hardware Setup
Expected time of completion: 10 min

### 1.1 Validate Encoders
Run `encoder_test.cpp` to validate your encoder setup.

### 1.2 Validate Motors
Run `motor_drive_test.cpp` to validate your motor setup.

### 1.3 Validate Joystick
Run `joystick_test.cpp` to validate your joystick setup.

## 2 Potentiometers
Expected time of completion: 25 min

### 2.1 Wire Potentiometers

We will be using potentiometers to tune our PID controller. First, please wire 3 potentiometers.

<details>
    <summary><i> What is a potentiometer?</i>
    </summary>
  A potentiometer is an electrical component that functions as a variable resistor or a voltage divider. It consists of a resistive element, such as a carbon track, and a movable wiper contact that slides along the element. By moving the wiper, you can change the resistance between the wiper and each end of the track, which allows you to adjust the level of current flowing through a circuit, or to change the voltage at the wiper, which can be used to control various devices such as the volume on a radio or the position of a servo motor in robotics.
  </details>

### 2.2 Read Potentiometers
Open `lab_code/potentiometer_test.cpp` and complete the `TODO`s.

## 3 Forward Kinematics

First, derive the forward kinematic equations for a 2-DoF arm. In other words, derive equations for `x` and `y` in terms of <code>Θ<sub>1</sub></code> and <code>Θ<sub>2</sub></code>.

<p align="center">
<img src="./.images/2dofarm.png" alt="drawing" width="300"/>
</p>

<details>
<summary><i> What is forward kinematics? </i></summary>

Forward kinematics answers the question, "Given the angles of the robot's joints, what are the x, y coordinates of the robot's hand?" For more, refer to lecture 2!

</details>

To validate your derived equations, run `kinematics.cpp` and `forward_kinematics_test.cpp`.

## 4 Validate Serial Read

## 5 Tune PID Using Potentiometers

### 
First, set the setpoint to be `(pi/2, 0)` in joint space. 

## 3 Feedback Form

Before you leave, please fill out https://tinyurl.com/212-feedback. 

| :white_check_mark: CHECKOFF X :white_check_mark:   |
|:---------------------------------------------------|
| Show the feedback form completion screen to a TA or LA. |


[^1]: Version 1 - 2024: Jinger Chong, Josh Sohn
