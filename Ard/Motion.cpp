#include <Wire.h>
#include "Motion.h"
#include <Adafruit_MotorShield.h>

Motion::Motion(int lf,  int lb, int rf, int rb){
  _AFMS = Adafruit_MotorShield();
  
  //initialize motors
  //_lf - left front motor
  //_rf - right front motor
  //_rb - right back motor
  //_lb - left back motor
  _lf = _AFMS.getMotor(lf);
  _lb = _AFMS.getMotor(lb);
  _rf = _AFMS.getMotor(rf);
  _rb = _AFMS.getMotor(rb);
}

//stop ceases all motion of motors
Motion::stop(){
    _lf->run(RELEASE);
    _lb->run(RELEASE);
    _rf->run(RELEASE);
    _rb->run(RELEASE);
}

Motion::rotate(bool right){
    this->stop();
    if(right == true){
        _lf->run(FORWARD);
        _lb->run(FORWARD);
        _rf->run(BACKWARD);
        _rb->run(BACKWARD);
    }else{
        _lf->run(BACKWARD);
        _lb->run(BACKWARD);
        _rf->run(FORWARD);
        _rb->run(FORWARD);
    }
}

Motion::linear(bool forward){
    if(forward == true){
        _lf->run(FORWARD);
        _lb->run(FORWARD);
        _rf->run(FORWARD);
        _rb->run(FORWARD);
    }else{
        _lf->run(BACKWARD);
        _lb->run(BACKWARD);
        _rf->run(BACKWARD);
        _rb->run(BACKWARD);
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

Motion::begin(){
    int speed = 200;
    _AFMS.begin();
    _lf->setSpeed(speed);
    _lb->setSpeed(speed);
    _rf->setSpeed(speed);
    _rb->setSpeed(speed);
    this->stop();
}