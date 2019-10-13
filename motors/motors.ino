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
  //while (! Serial);
  //Serial.println("Speed 0 to 255");
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
    
    // rotate left side counter in reverser
    digitalWrite(lfWheel, power[int(reverse)]); // Turn HIGH motor A //low - for forward
    digitalWrite(lbWheel, power[int(!reverse)]); //high 
    analogWrite(ENA, speed); // give power to left motors

    digitalWrite(rfWheel, power[int(!reverse)]); // turn HIGH motor B //high
    digitalWrite(rbWheel, power[int(reverse)]);  //low
    analogWrite(ENB, speed); //give power to right motors
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
