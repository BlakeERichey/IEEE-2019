#include <MPU9250.h>

MPU9250 IMU(Wire,0x68);
int status;

void setup() {
  // put your setup code here, to run once:

  //Serial for displaying data
  Serial.begin(9600);
  while(!Serial) {}

  //start communicating with IMU
  status = IMU.begin();
  if (status < 0) {
    Serial.println("IMU initialization unsuccessful");
    Serial.println("Check IMU wiring or try cycling power");
    Serial.print("Status: ");
    Serial.println(status);
    while(1) {}
  }

  //calibrate
}

void loop() {
  // put your main code here, to run repeatedly:

  int initYVelo =0;
  int endYVelo;
  int dTime = .01;
  
  //read sensor
  IMU.readSensor();

  int y1=IMU.getAccelY_mss();
  
  Serial.print(IMU.getAccelX_mss(),6);
  Serial.print("\t");
  Serial.print(IMU.getAccelY_mss(),6);
  Serial.print("\t");
  Serial.print(IMU.getAccelZ_mss(),6);
  Serial.print("\n");
  
  delay(100);
}
