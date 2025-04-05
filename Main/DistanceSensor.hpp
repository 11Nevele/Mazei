#ifndef DISTANCESENSOR_HPP
#define DISTANCESENSOR_HPP

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <SparkFun_I2C_Mux_Arduino_Library.h>  
#include <Adafruit_VL53L0X.h>

class DistanceSensor
{
  private:
  const int NUMBER_OF_SENSORS = 3;
  int distances[3]{};
  Adafruit_VL53L0X* distanceSensor[3];
  QWIICMUX myMux;
  public:
  DistanceSensor()
  {
    if (myMux.begin(0x70, Wire) == false) {
    Serial.println("MUX INITILIZATION FAILURE. SETUP HALTED");
    while (1);
    }
    Serial.println("MUX INITILIZATION SUCCESS");

    //Initialize the sensor
    Serial.println("Adafruit VL53L0X test");
    for (int i = 0; i < NUMBER_OF_SENSORS; i++){
      //everytime a distance sensor object is referenced it also references the distance sensor object
      
    }
    for (byte i = 0; i < NUMBER_OF_SENSORS; i++) {
      myMux.setPort(i);
      distanceSensor[i] = new Adafruit_VL53L0X();
      delay(100);
      if (distanceSensor[i]->begin() != 0)  //Begin returns 0 on a good init
      {
        Serial.print("DISTANCE SENSOR ");
        Serial.print(i);
        Serial.println("  INITILIZATION FAILURE.");
      } else {
        //Configure each sensor
        Serial.print("Sensor ");
        Serial.print(i);
        Serial.println(" configured");
      }
    }
  }
  void Debug()
  {
    Serial.print("[DEBUG]::");
    for(int i = 0; i < NUMBER_OF_SENSORS; ++i)
    {
      
      Serial.print("Sensor ");
      Serial.print(i);
      Serial.print(": ");
      Serial.print(distances[i]);
      Serial.print("\t");
    }
    Serial.println();
  }
  //return -1 if invalid or distance to far
  int GetDistance(int i)
  {
    if(i >= NUMBER_OF_SENSORS)
      return -1;
    return distances[i];
  }
  void Update()
  {
    for (byte i = 0; i < NUMBER_OF_SENSORS; i++) 
    {
      VL53L0X_RangingMeasurementData_t measure;
      myMux.setPort(i);
      distanceSensor[i]->rangingTest(&measure, false);  // pass in 'true' to get debug data printout!
    
      if (measure.RangeStatus != 4) {  // phase failures have incorrect data
        distances[i] = measure.RangeMilliMeter;
      } else {
        distances[i] = -1;
      }
  
    }
  }
  
};

#endif