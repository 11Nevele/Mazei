#include "Robot.h"
#include "RobotConfig.h"

Robot::Robot():leftCamera(leftCamerac1, leftCamerac2, leftCameral1, leftCameral2), 
rightCamera(leftCamerac1, leftCamerac2, leftCameral1, leftCameral2),
drive(),
// gyro(),
colorSensor(colorS0, colorS1, colorS2, colorS3, colorOut)
{

}

void Robot::Start()
{
  while(true)
  {
    int t = leftCamera.GetLetter();
    int color = leftCamera.GetColor();
    if(color == 1) //red
    {
      drive.Move(1);
    }
    Serial.println(t);
    delay(100);
  }
}