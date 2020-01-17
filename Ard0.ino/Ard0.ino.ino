#include "lcd.h"

const int NAME = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  delay(6000);

  //initialize lcd
  const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
  LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

  
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
}

void loop() {
  // put your main code here, to run repeatedly:
  sendData(NAME);
  delay(1000);
  recieveData();
}

void recieveData(){
  if (Serial.available() > 0){//is a char available?
    char msg = Serial.read();      //get the character
    //Serial.println(msg);
    printLCD("value recieved",double(msg),true);
  }
}

void sendData(int val){
  Serial.println(val);
  String root = "pi";//sets pi to active
}
