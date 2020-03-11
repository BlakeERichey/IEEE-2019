#include <Servo.h>
#include "pickup.h"
#include "motion.h"
#include <LSS.h>


const int NAME = 1;
String active = "pi";

//Configure arm
// ID set to default LSS ID = 0
#define LSS_ID		(0)
#define LSS_BAUD	(LSS_DefaultBaud)
// Create one LSS object
LSS myLSS = LSS(LSS_ID);

void setup() {
  // Initialize the LSS bus
	LSS::initBus(Serial, LSS_BAUD);

	// Initialize LSS to position 0.0 �
	myLSS.move(0);

  // Wait for it to get there
	delay(2000);

  // Serial.begin(9600);
  // Serial.println("Waiting for instructions...");
}

void loop() {
  runCommand(7);
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
    case 5: //CLOSE FLIPPERS
      if(flippersOpen){
        toggleFlippers();
      }
      break;
    case 6: //CLOSE CLAW
      if(clawOpen){
        toggleClaw();
      }
      break;
    case 7: //RAISE ARM
    // Serial.println("Raising arm");
      // Send LSS to half a turn counter-clockwise from zero (assumes gyre = 1)
      myLSS.moveT(-700,2000);

      // Wait for one second
      delay(1500);

        delay(10000);
      // Send LSS to half a turn clockwise from zero (assumes gyre = 1)
      myLSS.moveT(700,2000);

      // Wait for one second
      delay(5000);
      break;
  }
}
