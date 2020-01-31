#include "MPU9250.h"

// an MPU9250 object with the MPU-9250 sensor on I2C bus 0 with address 0x68
MPU9250 IMU(Wire,0x68);
int status;
double accelError[3];
double gyroError[3];

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
  
  IMU.readSensor();
  //margin of error is .025 m/(s^2);
  accelError[3] = {IMU.getAccelX_mss(),IMU.getAccelY_mss(),IMU.getAccelZ_mss()};
  gyroError[3] = {Double(IMU.getGyroX_rads()),DOuble(IMU.getGyroY_rads()),Double(IMU.getGyroZ_rads())};
}

void loop() {
  // read the sensor
  IMU.readSensor();
  
  double accel0[3] = {IMU.getAccelX_mss()-accelError[0],IMU.getAccelY_mss()-accelError[1],IMU.getAccelZ_mss()-accelError[2]};
  double gyro0[3] = {IMU.getGyroX_rads()-gyroError[0],IMU.getGyroY_rads()-gyroError[1],IMU.getGyroZ_rads()-gyroError[2]};
  double time1 = micros();

  //while no input to read 
  do{
    
    //calculate displacement between last point and current point
    
    
    //calculate angle change between last angle and current angle
  
  }while(!(Serial.available()>0));
  

  
  
  //delay(0);
}

void recieveData(){
  if (Serial.available() > 0){//is a char available?
    char msg = Serial.read();      //get the character
    //Serial.println(msg);
  }
}

void sendData(int val){
  Serial.println(val);
  String root = "pi";//sets pi to active
}
