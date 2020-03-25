#include <Servo.h>
#include "Motion.h"
#include "Servos.h"


const int NAME = 1;
String active = "pi";

//Attach DC motors
Motion motors(
  3,            //left front wheel
  4,            //left back wheel
  2,            //right front wheel
  1             //right back wheel
);

//Attach Servos for claw and flippers
Servos servos(
  9,            //claw pin
  4,           //left flipper
  3            //right flipper
);

void setup() {
  Serial.begin(9600);
  motors.begin();
  servos.begin();

  while(active == "pi"){
    Serial.println(NAME);
    delay(1000);
    if(Serial.available() > 0){
      active = "ard";
    }
  }

  servos.openClaw();
  servos.openFlippers();

  // Serial.println("Setup Complete.");
}

void loop() {
  // testServos();
  // testMotion();
  recieveData();
}

void recieveData(){
  if (Serial.available() > 0){//is a char available?
    active = "ard";                //sets ard to active
    char msg = Serial.read();      //get the character
    runCommand(int(msg));
  }
}

void runCommand(int action){
  switch(action%48){
    case 0:               //STOP MOTORS
      motors.stop();
      break;
    case 1:               //MOVE FORWARD
      motors.forward();
      break;
    case 2:               //MOVE BACKWARD
      motors.backward();
      break;
    case 3:               //ROTATE RIGHT
      motors.turnRight();
      break;
    case 4:               //ROTATE LEFT
      motors.turnLeft();
      break;  
    case 5:               //CLOSE FLIPPERS
      servos.closeFlippers();
      break;
    case 6:               //OPEN FLIPPERS
      servos.openFlippers();
      break;
    case 7:               //CLOSE CLAW
      servos.closeClaw();
      break;
    case 8:               //OPEN CLAW
      servos.openClaw();
      break;
    // case 9:               //RAISE ARM
    //   break;
    
    //Special case must be addressed since requires 2 bytes
    // case 10:              //LOWER ARM
    //   break;
  }
}


void testMotion(){
  runCommand(1);
  delay(1000);
  runCommand(0);
  delay(1000);
  runCommand(2);
  delay(1000);
  runCommand(0);
  delay(1000);

  runCommand(3);
  delay(1000);
  runCommand(0);
  delay(1000);
  runCommand(4);
  delay(1000);
  runCommand(0);
  delay(1000);
}

void testServos(){
  // servos.closeClaw();
  // delay(2000);
  // servos.openClaw();
  // delay(2000);
  servos.closeFlippers();
  delay(2000);
  servos.openFlippers();
  delay(2000);
}