#ifndef MOTOR_H
#define MOTOR_H
#include <Adafruit_MotorShield.h>
class Motor
{
  public:
  Motor();
  void Init(Adafruit_MotorShield& AFMS, int id);
  void SetVelocity(double);
  private:
  int m_ID;
  Adafruit_DCMotor* m_Motor;
};
#endif