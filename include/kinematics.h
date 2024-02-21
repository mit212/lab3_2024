#ifndef KINEMATICS
#define KINEMATICS

#include <math.h>

# define L1 0.169 // m
# define L2 0.209 // m

#define THETA1_OFFSET M_PI/2.0

struct JointSpace {
    double theta1; // radians
    double theta2; // radians
};

struct TaskSpace {
    double x; // m 
    double y; // m
};

TaskSpace forwardKinematics(JointSpace state);
JointSpace inverseKinematics(TaskSpace point);

#endif