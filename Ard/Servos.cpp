#include <Servo.h>
#include "Servos.h"
#include <Arduino.h>
#include <LSS.h>

// ID set to default LSS ID = 0
#define LSS_ID		(0)
#define LSS_BAUD	(LSS_DefaultBaud)

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
  _arm.moveT(700, 2000);
  delay(2050);
}

Servos::lowerArm(){
  _arm.moveT(-700, 2000);
  delay(2050);
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
  
  //Initialize arm and move to 0deg
  _arm = LSS(LSS_ID);
  LSS::initBus(Serial1, LSS_BAUD);
  _arm.move(0);
  delay(2000);
}