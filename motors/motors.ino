int lfWheel = 1; //left front
int rfWheel = 2; //right front
int rbWheel = 3; //right back
int lbWheel = 4; //left back

int ENA = 9;  //left linear movement
int ENB = 10; //right linear movement
 
void setup() 
{ 
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  //configure wheel motors
  pinMode(lfWheel, OUTPUT);
  pinMode(rfWheel, OUTPUT);
  pinMode(rbWheel, OUTPUT);
  pinMode(lbWheel, OUTPUT);
  Serial.begin(9600);
} 
 
 
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
