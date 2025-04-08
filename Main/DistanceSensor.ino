#include "DistanceSensor.h"

  DistanceSensor::DistanceSensor()
  {
    while (!Serial) {
      delay(1);
    }
    distanceSensor = new Adafruit_VL53L0X*[NUMBER_OF_SENSORS + 1];
    if (myMux.begin(0x70, Wire) == false) {
      Serial.println("MUX INITILIZATION FAILURE. SETUP HALTED");
    }

    Serial.println("MUX INITILIZATION SUCCESS");

    //Initialize the sensor
    Serial.println("Adafruit VL53L0X test");

    for (byte i = 1; i <= NUMBER_OF_SENSORS; i++) {
      myMux.setPort(i);
      delay(100);
      distanceSensor[i] = new Adafruit_VL53L0X();
      delay(100);
      if (distanceSensor[i]->begin() != 0)  //Begin returns 0 on a good init
      {
        Serial.print("DISTANCE SENSOR ");
        Serial.print(i);
        Serial.println("  INITILIZATION FAILURE.");
      } else {
        
        distanceSensor[i]->configSensor(Adafruit_VL53L0X::VL53L0X_SENSE_HIGH_ACCURACY);
        //Configure each sensor
        Serial.print("Sensor ");
        Serial.print(i);
        Serial.println(" configured");
      }
    }
  }
  void DistanceSensor:: Debug()
  {
    Serial.print("[DEBUG]::");
    for(int i = 1; i <= NUMBER_OF_SENSORS; ++i)
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
  int DistanceSensor:: GetDistance(int i)
  {
    ++i;
    if(i > NUMBER_OF_SENSORS)
      return -1;
    return distances[i];
  }

  void DistanceSensor:: Update()
  {
    int sums[NUMBER_OF_SENSORS + 1]{};
    for(int i = 0; i < 1; ++i)
    {
      for (byte i = 1; i <= NUMBER_OF_SENSORS; i++) 
      {
        VL53L0X_RangingMeasurementData_t measure;
        myMux.setPort(i);
        distanceSensor[i]->rangingTest(&measure, false);  // pass in 'true' to get debug data printout!
      
        if (measure.RangeStatus != 4 && sums[i] != -1)   
        {  
          sums[i] += measure.RangeMilliMeter;
        } else {
          sums[i] = -1;
        }
    
      }
    }
    for(int i = 1; i <= NUMBER_OF_SENSORS; ++i)
    {
      if(sums[i] == -1)
        distances[i] = -1;
      else
        distances[i] = sums[i] / 1;
    }
    
  }
  