/*
    Initializes servos for flippers and claw V.I.C.T.O.R.
*/
#ifndef Servos_h
#define Servos_h
#include <Servo.h>

class Servos{
  public:
    bool isClawClosed;
    bool isFlippersClosed;
    
    Servos(int clawPin,  int leftFlipper, int rightFlipper);
    raiseArm(); 
    lowerArm();
    openClaw();
    closeClaw();
    openFlippers();
    closeFlippers();
  private:
    Servo _claw, _lFlipper, _rFlipper;
    int _openClawAngle, _closeClawAngle; //claw closed and open angles
    int _openFlipperAngle, _closeFlipperAngle; //flippers closed and open angles
};

#endif