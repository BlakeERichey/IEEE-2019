#if ARDUINO >= 100
#include "Arduino.h"
#endif
#include <Servo.h>

const int NAME = 1;
String active = "pi";

//servo pins
const int clawPin = 3;

//variables
bool clawOpen = true;
void setup() {
  Servo Claw;
  Claw.attach(clawPin);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  toggleClaw();
  delay(2000);
  // if(active == "pi"){
  //   sendData(NAME);
  //   delay(100);
  //   recieveData();
  // }else{
  //   recieveData();
  // }
}

void recieveData(){
  if (Serial.available() > 0){//is a char available?
    active = "ard";                //sets ard to active
    char msg = Serial.read();      //get the character
    runCommand(int(msg));
  }
}

void sendData(int val){
  Serial.println(val);
}

void toggleClaw(){
  if (clawOpen) {
    claw.write(180);
  }else{
    claw.write(0);
  }
  clawOpen = !clawOpen;
}

void runCommand(int action){
  switch(action%48){
    case 0:
      stopMotors();
      break;
    case 1:
      linear(true); //move forward
      break;
    case 2:
      linear(false); //move backward
      break;
    case 3:
      rotate(true); //rotate right
      break;
    case 4:
      rotate(false); //rotate left
      break;  
  }
}
