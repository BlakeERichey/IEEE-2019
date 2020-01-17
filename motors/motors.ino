int lfWheel = 1; //left front
int lfWheelReverse = 2; 
int rfWheel = 3; //right front
int rfWheelReverse = 4;
int rbWheel = 5; //right back
int rbWheelReverse = 6;
int lbWheel = 7; //left back
int lbWheelReverse = 8;


int ENLF = 8;  //left linear movement
int ENRF = 13;  //left linear movement
int ENRB = 7; //right linear movement
int ENLB = 2; //right linear movement





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
  linear(false);
  delay(5000);
  stop_motors();
  delay(2000);
  linear(true);
  delay(5000);
  stop_motors();
  delay(2000);
}

void linear(bool forward){
  //Initialize the power range
  int power[] = {LOW, HIGH};
  stop_motors();
  int speed = 200; //0 <= speed <= 255

  // 
  digitalWrite(lfWheel, power[int(forward)]); //low - for forward
  digitalWrite(lbWheel, power[int(forward)]); //high for forward
  digitalWrite(rfWheel, power[int(forward)]); //low - for forward
  digitalWrite(rbWheel, power[int(forward)]); //high for forward
  analogWrite(ENA, speed); // give power to left motors
   
    
  
}

void stop_motors(){
  int speed = 0;
  analogWrite(ENA, speed);
  analogWrite(ENB, speed);
}

void linear(bool reverse){ //move forward, if reverse move backward
    int power[] = {LOW, HIGH};
    stop_motors();
    int speed = 200; //0 <= speed <= 255


    
    // rotate left side
    digitalWrite(lfWheel, power[int(reverse)]); //low - for forward
    digitalWrite(lbWheel, power[int(!reverse)]); //high for forward
    analogWrite(ENA, speed); // give power to left motors

    //rotate right side
    digitalWrite(rfWheel, power[int(!reverse)]); //high for forward
    digitalWrite(rbWheel, power[int(reverse)]);  //low for forward
    analogWrite(ENB, speed); //give power to right motors
}
