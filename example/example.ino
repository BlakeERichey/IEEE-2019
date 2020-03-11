// #include "Motion.h"
#include <AFMotor.h>

//Attach DC motors
Motion motors(3,4,2,1);

void setup(){
}

void loop(){
    motors.forward();
    delay(1500);
    motors.stop();
    delay(1500);
    motors.backward();
    delay(1500);
    motors.turnRight();
    delay(1500);
    motors.turnLeft();
    delay(1500);
}