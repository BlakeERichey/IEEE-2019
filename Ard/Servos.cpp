#include <Servo.h>
#include "Servos.h"
#include <Arduino.h>

Servos::Servos(int clawPin, int leftFlipper, int rightFlipper){
  isClawClosed       = false;
  isFlippersClosed   = false;

  _openClawAngle     = 180;
  _closeClawAngle    = 146;
  _openFlipperAngle  = 100;
  _closeFlipperAngle =  50;

  _claw.attach(clawPin);
  _lFlipper.attach(leftFlipper);
  _rFlipper.attach(rightFlipper);
}

Servos::raiseArm(){
  //not implemented
}

Servos::lowerArm(){
  //not implemented
}

Servos::openClaw(){
  for(int pos = _closeClawAngle; pos >= _openClawAngle; pos -= 1) {
    _claw.write(pos);
    delay(15);
  }
  isClawClosed = false;
}

Servos::closeClaw(){
  for (int pos = _openClawAngle; pos <= _closeClawAngle; pos += 1) {
    _claw.write(pos);
    delay(15);
  } 
  isClawClosed = true;
}

Servos::openFlippers(){
  int opened = _openFlipperAngle;
  int closed = _closeFlipperAngle;

  for (int pos = closed; pos <= opened; pos += 1) {
    _lFlipper.write(pos);
    _rFlipper.write(opened+closed-(pos-closed));
    delay(20);
  }
  
  isFlippersClosed = false;
}

Servos::closeFlippers(){
  int opened = _openFlipperAngle;
  int closed = _closeFlipperAngle;

  for (int pos = opened; pos >= closed; pos -= 1) {
    _lFlipper.write(pos);
    _rFlipper.write(opened+(opened-pos));
    delay(40);
  }

  isFlippersClosed = true;
}