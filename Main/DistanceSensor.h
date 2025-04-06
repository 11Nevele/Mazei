#ifndef DISTANCESENSOR_HPP
#define DISTANCESENSOR_HPP

#include <Wire.h>
// #include <Adafruit_Sensor.h>
#include <SparkFun_I2C_Mux_Arduino_Library.h>  
#include <Adafruit_VL53L0X.h>

class DistanceSensor
{
  private:
  const int NUMBER_OF_SENSORS = 4;
  int distances[4 + 1]{};
  Adafruit_VL53L0X** distanceSensor;
  QWIICMUX myMux;
  public:
  DistanceSensor();
  void Debug();
  //return -1 if invalid or distance to far
  int GetDistance(int i);
  void Update();
  
};

#endif