/*
    Initializes motors for movement for V.I.C.T.O.R.
*/
#ifndef Motion_h
#define Motion_h
#include <AFMotor.h>

class Motion{
    public:
        Motion(int lf,  int lb, int rf, int rb);
        stop();
        forward();
        backward();
        turnLeft(); 
        turnRight();
    private:
        AF_DCMotor _lf, _rf, _rb, _lb;
        rotate(bool right);
        linear(bool forward);
};

#endif