#include <Servo.h>
#include "Motion.h"
#include "Servos.h"


const int NAME = 0;
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
  7,            //claw pin
  10,           //left flipper
  11            //right flipper
);

void setup() {
  Serial.begin(9600);

  while(active == "pi"){
    Serial.println(NAME);
    if(Serial.available() > 0){
      active = "ard";
    }
  }

  Serial.println("Setup Complete.");
}

void loop() {
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
    case 9:               //RAISE ARM
      break;
    
    //Special case must be addressed since requires 2 bytes
    case 10:              //LOWER ARM
      break;
  }
}
