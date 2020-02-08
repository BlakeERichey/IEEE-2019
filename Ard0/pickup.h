#include <Servo.h>
//servo pins
#define clawPin 7
// #define flippers 9;

#define opened 146 //claw is open at this angle
#define closed 180 //claw is closed at this angle

//variables
bool clawOpen = true;
bool flippersOpen = true;

//initialize components
Servo Claw;

void toggleClaw(){
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

//void toggleFlippers(){
//  if(flippersOpen){
//    Flipper.write(110);
//  }{
//    Flipper.write(80);
//  }
//  flippersOpen = !flippersOpen;
//}
