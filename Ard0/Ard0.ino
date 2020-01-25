#if ARDUINO >= 100
#include "Arduino.h"
#endif
//+#include "lcd.h"
#include "motion.h"

const int NAME = 0;
String active = "pi";

void setup() {
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
  // put your setup code here, to run once:
  Serial.begin(9600);

  ////initialize lcd
  //  const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
  //  LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
  //
  //  
  //  // set up the LCD's number of columns and rows:
  //  lcd.begin(16, 2);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(active == "pi"){
    sendData(NAME);
    delay(100);
    recieveData();
  }else{
    recieveData();
  }
}

void recieveData(){
  if (Serial.available() > 0){//is a char available?
    active = "ard";                //sets ard to active
    char msg = Serial.read();      //get the character
    runCommand(int(msg));
  }
}

void sendData(int val){
  Serial.println(val);
}

void runCommand(int action){
  switch(action%48){
    case 0:
      stopMotors();
      break;
    case 1:
      linear(true); //move forward
      break;
    case 2:
      linear(false); //move backward
      break;
    case 3:
      rotate(true); //rotate right
      break;
    case 4:
      rotate(false); //rotate left
      break;  
  }
}
