#ifndef ROBOT_H
#define ROBOT_H
#include<Wire.h>
#include <Adafruit_MotorShield.h>
#include "Drivetrain.h"
#include "Camera.h"
#include <MPU6050_light.h>
class Robot
{
  public:
  Robot();
  void Start();
  void Update();


  private:
  Drivetrain drive;
  Camera leftCamera, rightCamera;
  MPU6050 mpu;
};

#endif