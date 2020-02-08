#if ARDUINO >= 100
#include "Arduino.h"
#endif
#include <Servo.h>
#include "Adafruit_VL6180X.h"

const int NAME = 1;
String active = "pi";

//servo pins
const int clawPin = 3;
const int flippers = 2;

//variables
bool clawOpen = true;
bool flippersOpen = true;

//initialize components
Servo Claw;
Servo Flipper;
Adafruit_VL6180X vl = Adafruit_VL6180X();
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

double getRange(){
  double range = -1.0;
  uint8_t status = vl.readRangeStatus();

  if (status == VL6180X_ERROR_NONE) {
    uint8_t range = vl.readRange();
    Serial.print("Range: "); Serial.println(range);
  }

  return range;
}