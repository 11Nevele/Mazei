#include "RobotConfig.h"

class Robot
{
  public:
  Robot():leftCamera(leftCamerac1, leftCamerac2, leftCameral1, leftCameral2), 
  rightCamera(leftCamerac1, leftCamerac2, leftCameral1, leftCameral2),
  drive(),
  gyro(),
  colorSensor(colorS0, colorS1, colorS2, colorS3, colorOut)
  {

  }
  void Start()
  {
    while(true)
    {
      //drive.Move(1);
      delay(10);
    }
  }
  void Update(){};


  private:
  Drivetrain drive;
  Camera leftCamera, rightCamera;
  ColorSensor colorSensor;

};

