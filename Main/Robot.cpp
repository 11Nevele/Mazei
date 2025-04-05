#include "Robot.h"
#include "RobotConfig.h"
#include "Tile.hpp"

Robot::Robot():leftCamera(leftCamerac1, leftCamerac2, leftCameral1, leftCameral2), 
rightCamera(leftCamerac1, leftCamerac2, leftCameral1, leftCameral2),
drive(),
gyro(),
colorSensor(colorS0, colorS1, colorS2, colorS3, colorOut)
{

}


double const ROTATION_ERROR = 0.5, ROTATION_RATE_ERROR = 0.5; 

static bool Robot::CheckRotationFinished(double target, double cur, double rate)
{
    bool ucRange = fabs(target - cur) < ROTATION_ERROR;
    bool rateRange = fabs(rate) < ROTATION_RATE_ERROR;
    return ucRange && rateRange ;
}

void Robot::Turn(double target){
  double kp = 0.033, ki = 0, kd = 0.33; 
  PID pid(kp, ki,kd);
   
  double curRotation  = gyro.GetYaw();
  const double baseRotation = curRotation;
  double st = millis();
  double waitTime = 1200;
  delay(10);
  while(!CheckRotationFinished(baseRotation + target, curRotation, pid.rateError))
  {        
      curRotation = gyro.GetYaw();
      double curError = baseRotation + target - curRotation;

      double out = pid.GetPID(curError);

      // if(out > maxSpeed) out = maxSpeed;
      // else if(out < -maxSpeed) out = -maxSpeed;
      Serial.print("Roatation: ");
      Serial.print(curRotation);
      Serial.print(" OUT: ");
      Serial.println(out);
    
      drive.Turn(out);
      delay(10);
  }

  drive.Turn(0);
  delay(100);  
}

void Robot::Start()
{
  Tile maze[60][60];

  while(true)
  {

    gyro.Update();
    colorSensor.Update();
    colorSensor.Debug();
    delay(10);
  }
}