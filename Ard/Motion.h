/*
    Initializes motors for movement for V.I.C.T.O.R.
*/
#ifndef Motion_h
#define Motion_h
#include <Adafruit_MotorShield.h>

class Motion{
  public:
    Motion(int lf,  int lb, int rf, int rb);
    stop();
    forward();
    backward();
    turnLeft(); 
    turnRight();
  private:
    Adafruit_MotorShield _AFMS;
    Adafruit_DCMotor *_lf, *_rf, *_rb, *_lb;
    rotate(bool right);
    linear(bool forward);
};

#endif