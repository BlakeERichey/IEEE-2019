#include <Servo.h>
#include "Servos.h"
#include <Arduino.h>

Servos::Servos(int clawPin, int leftFlipper, int rightFlipper){
  isClawClosed       = true;
  isFlippersClosed   = true;

  _openClawAngle     = 135;
  _closeClawAngle    = 180;
  _openFlipperAngle  = 50;
  _closeFlipperAngle =  1;

  _clawPin      = clawPin;
  _leftFlipper  = leftFlipper;
  _rightFlipper = rightFlipper;
}

Servos::raiseArm(){
  //not implemented
}

Servos::lowerArm(){
  //not implemented
}

Servos::openClaw(){
  if(isClawClosed){
    for(int pos = _closeClawAngle; pos >= _openClawAngle; pos -= 1) {
      _claw.write(pos);
      delay(20);
    }
  }
  isClawClosed = false;
}

Servos::closeClaw(){
  if(!isClawClosed){
    for (int pos = _openClawAngle; pos <= _closeClawAngle; pos += 1) {
      _claw.write(pos);
      delay(20);
    }
  }
  isClawClosed = true;
}

Servos::openFlippers(){
  int opened = _openFlipperAngle;
  int closed = _closeFlipperAngle;

  if(isFlippersClosed){
    for (int pos = closed; pos <= opened; pos += 1) {
      _lFlipper.write(pos);
      _rFlipper.write(max(opened-pos, 1));
      delay(20);
    }
  }

  
  isFlippersClosed = false;
}

Servos::closeFlippers(){
  int opened = _openFlipperAngle;
  int closed = _closeFlipperAngle;

  if(!isFlippersClosed){
    for (int pos = opened; pos >= closed; pos -= 1) {
      _lFlipper.write(pos);
      _rFlipper.write(opened-pos);
      delay(40);
    }
  }

  isFlippersClosed = true;
}

Servos::begin(){
  _claw.attach(_clawPin);
  _lFlipper.attach(_leftFlipper);
  _rFlipper.attach(_rightFlipper);
}