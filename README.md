# Lab 2: 2-DoF Robot Pt.1

2.12/2.120 Intro to Robotics  
Spring 2024[^1]

- [1 Hardware Assembly](#1-hardware-assembly)
- [2 Wiring and Validation](#2-wiring-and-validation)
  - [2.1 Microcontroller](#21-microcontroller)
  - [2.2 Motors](#22-motors)
  - [2.3 Encoders](#23-encoders)
- [3 Feedback Form](#3-feedback-form)
- [4 Adding the Joystick](#4-adding-the-joystick)
- [5 Moving in Joint Space](#5-moving-in-joint-space)
  - [5.1 Refactoring Code](#51-refactoring-code)
  - [5.2 Commanding the Robot](#52-commanding-the-robot)
  - [5.3 Draw A Line](#53-draw-a-line)
- [6 Moving in Cartesian Space](#6-moving-in-cartesian-space)
  - [6.1 Forward Kinematics](#61-forward-kinematics)
  - [6.2 Inverse Kinematics](#62-inverse-kinematics)
  - [6.3 Commanding the Robot](#63-commanding-the-robot)
  - [6.4 Draw Something](#64-draw-something)
- [X Optional](#x-optional)
  - [X.1 PID Tuning](#x1-pid-tuning)
  - [X.2 Setpoint Path](#x2-setpoint-path)
    
## 1 Hardware Assembly

Below is an image of the 2-DoF robot arm you will assemble. Completing this section should take less than 20 minutes, so please ask for help if you feel like you are taking longer! We want you to have enough time to complete the remaining sections.

<p align=center>
  <img src=./.images/0_full.png width=600>
</p>

Materials:

- 2 [arm links (low-side U-channel)](https://www.gobilda.com/1143-series-mini-low-side-u-channel-8-hole-216mm-length/)
- 3 [base mounts (U-channel)](https://www.gobilda.com/1120-series-u-channel-4-hole-120mm-length/)
- 2 [motors (60 RPM)](https://www.gobilda.com/5203-series-yellow-jacket-planetary-gear-motor-99-5-1-ratio-24mm-length-8mm-rex-shaft-60-rpm-3-3-5v-encoder/)
- 2 [hubs](https://www.gobilda.com/1310-series-hyper-hub-8mm-rex-bore/)
- [socket head bolts (M4)](https://www.gobilda.com/2800-series-zinc-plated-steel-socket-head-screw-m4-x-0-7mm-8mm-length-25-pack/)
- [hex nuts (M4)](https://www.gobilda.com/2811-series-zinc-plated-steel-hex-nut-m4-x-0-7mm-7mm-hex-25-pack/)
- marker holder

Steps:
1. Attach the 2 motors on either end of a single arm link.
    <p align=center>
      <img src=./.images/1_motors.png width=400>
    </p>

2. Add the hubs onto each shaft using 2 set screws.
    <p align=center>
      <img src=./.images/2_hub.png width=350>
    </p>

3. Attach the base made of 3 U-channels to one of the hubs.
    <p align=center>
      <img src=./.images/3_attach.png width=300>
    </p>

4. Attach a new arm to the other hub and attach the marker holder to the end of that arm.
    <p align=center>
      <img src=./.images/4_holder.png width=600>
    </p>
5. Use two clamps to hold the base down to the table.

## 2 Wiring and Validation

Similar to Lab 1, we also need to wire and validate the microcontroller, motors, and encoders.

### 2.1 Microcontroller

1. Plug the microcontroller in the breadboard so that the USB-C port is near the edge of the breadboard.
2. Use solid wires to connect the `3.3V` to both `+` rails and `GND` to both `-` rails.
   
    <details>
    <summary><i> What is a rail?</i>
    </summary>

    Rails on a breadboard refer to the two long strips labeled `+` and `-` on either side. They are typically located between red and blue lines parallel to the rails.
    </details>
3. Open the VSCode application. Click "File" on the upper-left corner then click "New Window". 
4. Clone this repository.
5. Run `blink_test.cpp`. The onboard LED should change colors.
    <details>
    <summary><i> How do I put the microcontroller in download mode again?</i>
    </summary>

    Press and hold `BOOT`. Click `RST` while still holding down `BOOT`. Let go of `BOOT`.
    </details>


### 2.2 Motors 

1. Wire the motors according to `include/pinout.h`. Remember to wire the `GND` pin of the motor driver to the `-` rail. 
2. Connect the button as an emergency stop to go between the motor driver and the power supply. 
3. Reduce the power supply output to about `4V`. **Remember, the motors are powerful. Always keep the workspace clear of obstacles (laptops) and hold on to the emergency stop button.**
4. Confirm that the motor driver has power. The yellow `PWR` LED should be on. If not, turn on the emergency stop button.
5. Push and hold the `M1A`, `M1B`, `M2A`, `M2B` buttons on the motor driver one at a time to check that the motors can spin in both directions. `M1` should correspond to the motor attached to the base. 
6. Turn off the emergency stop button. The emergency stop should always be off unless the motors need to move.
7. Make the arm point straight up in full extension. This is the default position the arm should be in **before running any code**. 
8.  Run `motor_drive_test.cpp`. You should see both motors turn slightly in both directions at two different speeds.
    <details>
    <summary><i> Nothing is happening?</i>
    </summary>

    Check that the motor driver has power by looking at the yellow `PWR` LED. If not, turn on the emergency stop button.
    </details>
9. Turn off the emergency stop button. The motor driver does not need power for the encoder wiring and validation.

### 2.3 Encoders 

1. Wire the encoders according to `include/pinout.h`. Use an extension cable for encoder 2.
2. Use zip ties to attach the wires encoder 2 to link 1 so that `M1` can rotate freely without snagging wires.
3. Run `encoder_basic_test.cpp` and open the Serial Monitor. Observe which turn directions make the encoder count increase and think about why this is the case.
4. Run `encoder_test.cpp`. Confirm that the position increases when turning link 1 counter-clockwise looking down at the table and decreases when turning link 2 counter-clockwise looking down at the table.

| :white_check_mark: CHECKOFF 1 :white_check_mark:   |
|:---------------------------------------------------|
| Demonstrate `encoder_test.cpp` to a TA or LA! |

## 3 Feedback Form

Before you leave, please fill out https://tinyurl.com/212-feedback and present the completion screen to a TA or LA. 

**LAB IS SET TO STOP HERE. EVERYTHING AFTER THIS POINT IS OPTIONAL AND WILL BE DONE 1 or 2 LABS FROM NOW.**

## 4 Adding the Joystick

Now that we have a validated 2-DoF robot, let's add a joystick to control it.

1. Wire the joystick according to the schematic on the board.
2. To validate that you can read the joystick input, run `joystick_test.cpp` and open the Serial Monitor. You should see joystick readings in the range `[-1, 1)`.

## 5 Moving in Joint Space

With the joystick in place, we can then use code to connect the joystick reading to the robot motion.

### 5.1 Refactoring Code

1. Open `include/joystick.h` and define a `struct` to store the `x` and `y` values of a joystick reading as integers.
    <details>
    <summary>  <i> What is a struct?</i></summary>

    A structure or `struct` is a user-defined data type that can group *members* of possibly different types into a single type. An example usage is shown below.
    ``` 
    struct Student {
      int id;
      float gpa;
    };

    Student bob(1, 2.0); // Initializes a Student variable called bob with id 1 and gpa 2.0
    bob.gpa = 2.3; // Updates the gpa member of bob to 2.3
    Serial.printf("GPA: %.2f\n", bob.gpa); // Prints the new gpa 2.3 in the Serial Monitor
    ```
    </details>

2. Open `lab_code/joystick.cpp` and complete the `TODO`s. 
3. Open `test_code/joystick_test.cpp` and complete the `TODO`s. 
4. Move `joystick_test.cpp` and `joystick.cpp` to the `robot/` directory. 
5. Run the new `joystick_test.cpp` and open the Serial Monitor. Confirm that your joystick readings are the same as before. 
    
### 5.2 Commanding the Robot

Open `lab_code/drawing.cpp` and complete all the `TODO 1`s. At a high level, the code should do the following:
   - reads the joystick
   - scales the joystick reading from `[-1, 1)` to `[-pi/2, pi/2)`
   - feeds the joystick reading to a position setpoint
   - smoothes the position setpoint using exponential smoothing
   - drives the motor using a PID controller

Simply put, the x-axis of the joystick controls the velocity of motor 1 and the y-axis of the joystick controls the velocity of motor 2. This is joint space!

### 5.3 Draw A Line
Attach a marker to the end of your 2-DoF robot and try drawing a straight line on your whiteboard. Make sure to move all 3 files `drawing.cpp`, `joystick.cpp`, and `kinematics.cpp` from `lab_code/` to `robot/`.

| :white_check_mark: CHECKOFF 2 :white_check_mark:   |
|:---------------------------------------------------|
| Show your work of art to a TA or LA! |

## 6 Moving in Cartesian Space

You may have noticed that it is quite difficult to draw something by controlling the motors individually. Since our desired output is in Cartesian space, we can use what we learned in lecture to command the robot in Cartesian space instead of joint space!

### 6.1 Forward Kinematics

First, derive the forward kinematic equations for a 2-DoF arm. In other words, derive equations for `x` and `y` in terms of <code>Θ<sub>1</sub></code> and <code>Θ<sub>2</sub></code>.

<p align="center">
<img src="./.images/2dofarm.png" alt="drawing" width="300"/>
</p>

| :white_check_mark: CHECKOFF 3 :white_check_mark:   |
|:---------------------------------------------------|
| Show your work of art to a TA or LA! |

<details>
<summary><i> What is forward kinematics? </i></summary>

Forward kinematics answers the question, "Given the angles of the robot's joints, what are the x, y coordinates of the robot's hand?" For more, refer to lecture 2!

</details>

Run `forward_kinematics_test.cpp`.

### 6.2 Inverse Kinematics

Using the forward kinematic equations you found, derive the inverse kinematic equations for a 2-DoF arm. In other words, derive equations for <code>Θ<sub>1</sub></code> and <code>Θ<sub>2</sub></code> in terms of `x` and `y`.

<details>
<summary><i> What is inverse kinematics? </i></summary>

It's the opposite of forward kinematics!
Put simply, forward inverse kinematics answers the question, "Given the desired x,y coordinates of the robot's hand, what should the angles of the robot's joints be?" For more, refer to lecture 2!

</details>

Then, translate your derived equations into code by completing the `TODO 2`s in `kinematics.cpp`.

To validate your derived equations, move `kinematics.cpp` and either `forward_kinematics_test.cpp` or `inverse_kinematics_test.cpp` to the `robot` directory and upload your code. When running `forward_kinematics_test.cpp`, you should see `x` and `y` reflect the position of the marker holder in real life. When running `inverse_kinematics_test.cpp`, you should see `theta1_error` and `theta2_error` be 0.

### 6.3 Commanding the Robot

Open `lab_code/drawing.cpp` and complete all the `TODO 2`s. This involves changing `new_setpoint1` and `new_setpoint2` in `drawing.cpp` from joint space to Cartesian space using `State inverseKinematics(Point endEffector)`.

### 6.4 Draw Something 

Finally, use the joystick to draw your masterpiece.

| :white_check_mark: CHECKOFF 4 :white_check_mark:   |
|:---------------------------------------------------|
| Show your (hopefully improved) work of art to a TA or LA! |

## X Optional

If you finished lab early, here's a few optional challenges you can try (in any order)!

### X.1 PID Tuning

Change the gains in `drawing.cpp` so that robot moves smoothly. 

### X.2 Setpoint Path

Make copy of `drawing.cpp` and modify it so that the end-effector of your robot follows a set path, e.g. a circle.

[^1]: Version 1 - 2024: Jinger Chong, Josh Sohn
