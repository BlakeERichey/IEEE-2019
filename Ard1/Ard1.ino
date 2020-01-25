#include "MPU9250.h"

// an MPU9250 object with the MPU-9250 sensor on I2C bus 0 with address 0x68
MPU9250 IMU(Wire,0x68);
int status;

void setup() {
  // serial to display data
  Serial.begin(9600);
  while(!Serial) {}

  // start communication with IMU 
  status = IMU.begin();
  if (status < 0) {
    Serial.println("IMU initialization unsuccessful");
    Serial.println("Check IMU wiring or try cycling power");
    Serial.print("Status: ");
    Serial.println(status);
    while(1) {}
  }
  // setting the accelerometer full scale range to +/-8G 
  IMU.setAccelRange(MPU9250::ACCEL_RANGE_8G);
  // setting the gyroscope full scale range to +/-500 deg/s
  IMU.setGyroRange(MPU9250::GYRO_RANGE_500DPS);
  // setting DLPF bandwidth to 20 Hz
  IMU.setDlpfBandwidth(MPU9250::DLPF_BANDWIDTH_20HZ);
  // setting SRD to 19 for a 50 Hz update rate
  IMU.setSrd(19);

}

void loop() {
  // read the sensor
  IMU.readSensor();
  time1 = micros();

  do{
    
    //calculate displacement between last point and current point

    //calculate angle change between last angle and current angle
  
  }while();
  

  
  
  //delay(0);
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
