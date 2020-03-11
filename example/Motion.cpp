#include "Motion.h"
#include <AFMotor.h>

Motion::Motion(int lf,  int lb, int rf, int rb)
    : _lf(lf), _rf(rf), _rb(rb), _lb(lb) {
    //initialize motors
    //_lf - left front motor
    //_rf - right front motor
    //_rb - right back motor
    //_lb - left back motor

    _lf.setSpeed(255);
    _lb.setSpeed(255);
    _rf.setSpeed(255);
    _rb.setSpeed(255);
}

//stop ceases all motion of motors
Motion::stop(){
    _lf.run(RELEASE);
    _lb.run(RELEASE);
    _rf.run(RELEASE);
    _rb.run(RELEASE);
}

Motion::rotate(bool right){
    this->stop();
    if(right == true){
        _lf.run(FORWARD);
        _lb.run(FORWARD);
        _rf.run(BACKWARD);
        _rb.run(BACKWARD);
    }else{
        _lf.run(BACKWARD);
        _lb.run(BACKWARD);
        _rf.run(FORWARD);
        _rb.run(FORWARD);
    }
}

Motion::linear(bool forward){
    if(forward == true){
        _lf.run(FORWARD);
        _lb.run(FORWARD);
        _rf.run(FORWARD);
        _rb.run(FORWARD);
    }else{
        _lf.run(BACKWARD);
        _lb.run(BACKWARD);
        _rf.run(BACKWARD);
        _rb.run(BACKWARD);
    }
}

Motion::forward(){
    this->linear(true);
}

Motion::backward(){
    this->linear(false);
}

Motion::turnRight(){
    this->rotate(true);
}

Motion::turnLeft(){
    this->rotate(false);
}