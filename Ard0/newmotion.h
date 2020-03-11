#include <AFMotor.h>

AF_DCMotor motor1(1); //Back Right
AF_DCMotor motor2(2); //Front Right
AF_DCMotor motor3(3); //Front Left
AF_DCMotor motor4(4); //Back Left


bool x;
bool y;



void forward_or_right(bool x) {
 
  //setup motors
  motor1.setSpeed(255);
  motor2.setSpeed(255);
  motor3.setSpeed(255);
  motor4.setSpeed(255);
 
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
 
 
  //Forward condition
if (x == y) {
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);

  delay(4000);
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
  delay(200);
 
}

//Rotate right condition
else if  (x != y){
 
  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);

  delay(4000);
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
  delay(200);
 
 
}

}
