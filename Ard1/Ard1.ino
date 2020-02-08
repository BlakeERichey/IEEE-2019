#if ARDUINO >= 100
#include "Arduino.h"
#endif
#include <Servo.h>

const int NAME = 1;
String active = "pi";

//servo pins
const int clawPin = 3;
const int flippers = 2;

//variables
bool clawOpen = true;
bool flippersOpen = true;
Servo Claw;
Servo Flipper;
void setup() {
  Claw.attach(clawPin);
  Flipper.attach(flippers);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  toggleFlippers();
  delay(2000);
}

void toggleClaw(){
  if (clawOpen) {
    Claw.write(180);
  }else{
    Claw.write(0);
  }
  clawOpen = !clawOpen;
}

toggleFlippers(){
  if(flippersOpen){
    for(int i = 0; i<180; i+=5){
      Flipper.write(i+1);
      delay(200);
    }
  }{
    Flipper.write(0);
  }
  flippersOpen = !flippersOpen;
}