int lfWheel = 6; //left front
int lfWheelReverse = 5; 
int rfWheel = 4; // right front
int rfWheelReverse = 3;
int rbWheel = 11; //right back
int rbWheelReverse = 12;
int lbWheel = 9; //left back
int lbWheelReverse = 10;


int ENLF = 7;  //left linear movement
int ENRF = 2;  //left linear movement
int ENRB = 13; //right linear movement
int ENLB = 8; //right linear movement

void setup() 
{ 
  // Used to power the sides of the robot
  pinMode(ENLF, OUTPUT);
  pinMode(ENRF, OUTPUT);
  pinMode(ENRB, OUTPUT);
  pinMode(ENLB, OUTPUT);
  
  //configure wheel motors- determine where the power is put 
  pinMode(lfWheel, OUTPUT);
  pinMode(lfWheelReverse, OUTPUT);
  pinMode(rfWheel, OUTPUT);
  pinMode(rfWheelReverse, OUTPUT);
  pinMode(rbWheel, OUTPUT);
  pinMode(rbWheelReverse, OUTPUT);
  pinMode(lbWheel, OUTPUT);
  pinMode(lbWheelReverse, OUTPUT);
  Serial.begin(9600);
} 
 
// Main fuction
void loop() 
{
  rotate(true);
  delay(2000);
  stop_motors();
  delay(2000);
  rotate(false);
  delay(2000);
  stop_motors();
  delay(2000);
}
  
void linear(bool forward){
  //Initialize the power range
  int power[] = {LOW, HIGH};
  stop_motors();
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
  stop_motors();
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

void stop_motors(){
  int speed = 0;
  analogWrite(ENLF, speed);
  analogWrite(ENRF, speed);
  analogWrite(ENRB, speed);
  analogWrite(ENLB, speed);
}
