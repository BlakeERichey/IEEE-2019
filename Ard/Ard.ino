#include <Servo.h>
#include "Motion.h"
#include "Servos.h"
#define MAX_BUFFER_LENGTH 2


const int NAME = 0;
String active = "pi";
char buffer[MAX_BUFFER_LENGTH]; //instruction buffer

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
  int len = 0;
  if (Serial.available() >= 0){
    while(Serial.available()>len){//is a char available?
      len = Serial.available();
      delay(5); //delay for new characters to arrive
      if(len>10){
        break;
      }
    }
  }
  String instr = ""; //instruction
  if(len>0){
    Serial.readBytes(buffer, len); //get the characters
    Serial.println(len);
    for(int i = 0; i<len; i++){ //exclude terminal character
      instr += String(int(buffer[i])-48);
    }
    Serial.println(instr);
    Serial.println(instr.toInt());
    runCommand(instr.toInt());
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
    
    //Special case must be addressed since requires 2 bytes
    case 9:               //RAISE ARM
      motors.forward();
      break;
    case 10:              //LOWER ARM
      motors.backward();
      break;
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
  servos.closeClaw();
  delay(2000);
  servos.openClaw();
  delay(2000);
  servos.closeFlippers();
  delay(2000);
  servos.openFlippers();
  delay(2000);
}