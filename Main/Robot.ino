#include "Robot.h"
#include "RobotConfig.h"

Robot::Robot():leftCamera(leftCamerac1, leftCamerac2, leftCameral1, leftCameral2), mpu(Wire), drive()
{

}

void Robot::Start()
{
  while(true)
  {
    int t = leftCamera.GetLetter();
    Serial.println(t);
    delay(100);
  }
}