#ifndef DRIVETRAIN_H
#define DRIVETRAIN_H
#include "Motor.h"
#include <Adafruit_MotorShield.h>
class Drivetrain
{
  public:
  Drivetrain();
  void Move(double);
  void Turn(double);

  private:
  Motor FL, FR, BL, BR;
  Adafruit_MotorShield AFMS;
};
#endif