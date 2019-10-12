int lfWheel = 1; //left front
int rfWheel = 2; //right front
int rbWheel = 3; //right back
int lbWheel = 4; //left back
 
void setup() 
{ 
  pinMode(lfWheel, OUTPUT);
  pinMode(rfWheel, OUTPUT);
  pinMode(rbWheel, OUTPUT);
  pinMode(lbWheel, OUTPUT);
  Serial.begin(9600);
  //while (! Serial);
  //Serial.println("Speed 0 to 255");
} 
 
 
void loop() 
{ 
    int speed = 200; //0= < speed <= 255
    if (speed >= 0 && speed <= 255){
      analogWrite(lfWheel, speed);
    }
}

void moveForward(){
  
}



/*
Adafruit Arduino - Lesson 15. Bi-directional Motor
*/
 
//int enablePin = 11;
//int in1Pin = 10;
//int in2Pin = 9;
//int switchPin = 7;
//int potPin = 0;
// 
//void setup()
//{
//  pinMode(in1Pin, OUTPUT);
//  pinMode(in2Pin, OUTPUT);
//  pinMode(enablePin, OUTPUT);
//  pinMode(switchPin, INPUT_PULLUP);
//}
// 
//void loop()
//{
//  int speed = analogRead(potPin) / 4;
//  boolean reverse = digitalRead(switchPin);
//  setMotor(speed, reverse);
//}
// 
//void setMotor(int speed, boolean reverse)
//{
//  analogWrite(enablePin, speed);
//  digitalWrite(in1Pin, ! reverse);
//  digitalWrite(in2Pin, reverse);
//}
