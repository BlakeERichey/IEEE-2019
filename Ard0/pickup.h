#include <Servo.h>
Servo Claw;
Servo Flipper;

bool clawOpen = true;
bool flippersOpen = true;

void toggleClaw(){
  if (clawOpen) {
    Claw.write(180);
  }else{
    Claw.write(0);
  }
  clawOpen = !clawOpen;
}

void toggleFlippers(){
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
