#ifndef ROBOT_H
#define ROBOT_H
#include<Wire.h>
#include <Adafruit_MotorShield.h>
#include "Drivetrain.h"
#include "Camera.h"
#include "Gyro.h"
#include "ColorSensor.hpp"
#include <Servo.h>
#include "DistanceSensor.hpp"

class Robot
{
  public:
  Robot();
  void Start();

  private:
  Drivetrain drive;
  Camera leftCamera, rightCamera;
  Gyro gyro;
  ColorSensor colorSensor;
  Servo servo;
  DistanceSensor distanceSensor;

};

#endif