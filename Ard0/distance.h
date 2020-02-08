#include "Adafruit_VL53L0X.h"
Adafruit_VL53L0X tof = Adafruit_VL53L0X();

double getRange(){
  double range = -1.0;
  VL53L0X_RangingMeasurementData_t measure;
    
  // Serial.print("Reading a measurement... ");
  tof.rangingTest(&measure, false); // pass in 'true' to get debug data printout!

  if (measure.RangeStatus != 4) {  // phase failures have incorrect data
    range = measure.RangeMilliMeter;
  }
  return range;
}
