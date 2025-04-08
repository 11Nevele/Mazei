#ifndef ROBOT_H
#define ROBOT_H
#include<Wire.h>
#include <Adafruit_MotorShield.h>
#include "Drivetrain.h"
#include "Camera.h"
#include "Gyro.h"
#include "ColorSensor.hpp"
#include "PID.h"
#include "Tile.hpp"
#include <Servo.h>
#include "Direction.hpp"
#include "DistanceSensor.h"

class Robot
{
  public:
  Robot();
  void Start();
  void Turn(double,double);
  void Move(double, double);
  void MovePID(double, double, double);
  bool CheckMovementFinished(double, double, double);
  bool CheckRotationFinished(double , double , double);
  void CheckVictum(int &vic);
  void Swipe();
  void Flash();
  double AngleDif(double from, double to)
  {
    double t = to - from;
    if(t > 180)
      t = t - 360;
    if(t < -180)
      t = t + 360;
    return t;
  }


  private:
  Drivetrain drive;
  Camera leftCamera, rightCamera;
  Gyro gyro;
  //ColorSensor colorSensor;
  Servo servo;
  DistanceSensor distanceSensor;
  Direction facing;
  Tile maze[30][30]{};
  int r =30, c = 30;
};

#endif