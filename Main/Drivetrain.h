#ifndef DRIVETRAIN_H
#define DRIVETRAIN_H
#include "Motor.h"
#include <Adafruit_MotorShield.h>
class Drivetrain
{
  public:
  Drivetrain();
  void Move(double);

  private:
  Motor FL, FR, BL, BR;
  Adafruit_StepperMotor *servo = AFMS.getStepper(200, 1);
  Adafruit_MotorShield AFMS;
};
#endif