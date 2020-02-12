#include <Servo.h>
//Servo pins
#define clawPin 7
#define lFlipper 10;
#define rFlipper 11;

//variables
bool clawOpen = true;
bool flippersOpen = true;

//initialize components
Servo Claw;
Servo FlipperLeft;
Servo FlipperRight;

void toggleClaw(){
  int opened = 146; //claw is open at this angle
  int closed = 180; //claw is closed at this angle

  if (clawOpen) { //close
    for (int pos = opened; pos <= closed; pos += 1) {
      Claw.write(pos);
      delay(15);
    } 
  }else{ //open
    for(int pos = closed; pos >= opened; pos -= 1) {
      Claw.write(pos);
      delay(15);
    } 
  }
  clawOpen = !clawOpen;
}

void toggleFlippers(){
  int opened = 100;  //flipper is open at this angle
  int closed = 50; //flipper is closed at this angle

  if (flippersOpen) { //close
    for (int pos = opened; pos >= closed; pos -= 5) {
      FlipperLeft.write(pos);
      FlipperRight.write(opened+(opened-pos));
      delay(100);
    }
  }else{ //open
    for (int pos = closed; pos <= opened; pos += 5) {
      FlipperLeft.write(pos);
      FlipperRight.write(opened+closed-(pos-closed));
      delay(100);
    } 
  }
  flippersOpen = !flippersOpen;
}
