#include "Motor.h"
#include <Adafruit_MotorShield.h>
void Motor::Init(Adafruit_MotorShield& AFMS, int id)
  {
    m_Motor = AFMS.getMotor(id);
    m_ID = id;
  }
Motor::Motor(){}
void Motor::SetVelocity(double spd)
{
  if(spd > 0)
    m_Motor->run(FORWARD);
  else if(spd < 0)
    m_Motor->run(BACKWARD), spd = -spd;
  else
    m_Motor->run(RELEASE);
  m_Motor->setSpeed(spd*255.0);
}