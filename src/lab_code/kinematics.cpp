#include "kinematics.h"
#include <math.h>

TaskSpace forwardKinematics(JointSpace state) {
    // Initializes a TaskSpace variable called point
    TaskSpace point; 

    // TODO 1: Modify the two lines below to use the forward kinematics equations you derived. 
    // You may need the variables: LINK1 (the length of link 1), LINK2 (the length of link 2), state
    // as well as the functions: double cos(double x), double sin(double x), double tan(double x).
    point.x = 0;
    point.y = 0;

    return point;
}

JointSpace inverseKinematics(TaskSpace point) {
    // Initializes a JointSpace variable called state
    JointSpace state; 

    // TODO 2: Modify the two lines below to use the inverse kinematics equations you derived. 
    // You may need the variables: LINK1, LINK2, point
    // as well as the functions: double atan2(double x, double y), double pow(double x, 2), double sqrt(double x)
    // If there are two possible configurations, you may choose either.
    state.theta1 = 0;
    state.theta2 = 0;

    // Makes sure state.theta1 and state.theta2 in the range [-pi/2, pi/2] 
    state.theta1 = atan2(sin(state.theta1), cos(state.theta1));
    state.theta2 = atan2(sin(state.theta2), cos(state.theta2));

    return state;
}