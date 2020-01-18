#define lfWheel 6 //left front
#define lfWheelReverse 5 
#define rfWheel 4 // right front
#define rfWheelReverse 3
#define rbWheel 11 //right back
#define rbWheelReverse 12
#define lbWheel 9 //left back
#define lbWheelReverse 10


#define ENLF 7  //left linear movement
#define ENRF 2  //left linear movement
#define ENRB 13 //right linear movement
#define ENLB 8 //right linear movement

void stopMotors(){
  int speed = 0;
  analogWrite(ENLF, speed);
  analogWrite(ENRF, speed);
  analogWrite(ENRB, speed);
  analogWrite(ENLB, speed);
}

void linear(bool forward){
  //Initialize the power range
  int power[] = {LOW, HIGH};
  stopMotors();
  int speed = 200; //0 <= speed <= 255
  
    
  digitalWrite(lfWheel, power[int(forward)]); //low - for forward
  digitalWrite(lbWheel, power[int(forward)]); //high for forward
  digitalWrite(rfWheel, power[int(forward)]); //low - for forward
  digitalWrite(rbWheel, power[int(forward)]); //high for forward
  
  digitalWrite(lfWheelReverse,power[int(!forward)]);
  digitalWrite(lbWheelReverse,power[int(!forward)]);
  digitalWrite(rfWheelReverse,power[int(!forward)]);
  digitalWrite(rbWheelReverse,power[int(!forward)]);

 // give power to left motor
  analogWrite(ENLF, speed);
  analogWrite(ENRF, speed);
  analogWrite(ENRB, speed);
  analogWrite(ENLB, speed);
}

void rotate(bool right){
  //Initialize the power range
  int power[] = {LOW, HIGH};
  stopMotors();
  int speed = 200; //0 <= speed <= 255

  digitalWrite(lfWheel, power[int(right)]);
  digitalWrite(lbWheel, power[int(right)]);
  digitalWrite(rfWheel, power[int(!right)]);
  digitalWrite(rbWheel, power[int(!right)]);

  digitalWrite(lfWheelReverse,power[int(!right)]);
  digitalWrite(lbWheelReverse,power[int(!right)]);
  digitalWrite(rfWheelReverse,power[int(right)]);
  digitalWrite(rbWheelReverse,power[int(right)]);

  analogWrite(ENLF, speed);
  analogWrite(ENRF, speed);
  analogWrite(ENRB, speed);
  analogWrite(ENLB, speed);
}
