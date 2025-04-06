#include "Robot.h"
#include "RobotConfig.h"
#include "Tile.hpp"
#include "Stack.h"
#include "Vector.hpp"

Robot::Robot()://leftCamera(leftCamerac1, leftCamerac2, leftCameral1, leftCameral2), 
//rightCamera(leftCamerac1, leftCamerac2, leftCameral1, leftCameral2),
distanceSensor(),
drive(),
gyro()
//colorSensor(colorS0, colorS1, colorS2, colorS3, colorOut),
//servo(),

{
  //servo.attach(servoPort);
}


double const ROTATION_ERROR = 0.5, ROTATION_RATE_ERROR = 0.5; 

bool Robot::CheckRotationFinished(double target, double cur, double rate)
{
    bool ucRange = fabs(target - cur) < ROTATION_ERROR;
    bool rateRange = fabs(rate) < ROTATION_RATE_ERROR;
    return ucRange && rateRange ;
}

void Robot::Turn(double target, double maxSpeed = 1.0){
  double kp = 0.01, ki = 0.001, kd = 0; 
  PID pid(kp, ki,kd);
   
  double curRotation  = gyro.GetYaw();
  double st = millis();
  double waitTime = 1500;
  delay(10);
  while(!CheckRotationFinished(target, curRotation, pid.rateError))
  {        
      
      curRotation = gyro.GetYaw();
      double curError = AngleDif(curRotation, target);
      
      double out = pid.GetPID(curError, st + waitTime < millis());

      if(out > maxSpeed) out = maxSpeed;
      else if(out < -maxSpeed) out = -maxSpeed;
      Serial.print("Error: ");
      Serial.print(curError);
      Serial.print(" OUT: ");
      Serial.println(out);
    
      drive.Turn(out);
      delay(10);
  }

  drive.Turn(0);
  delay(100);  
}

const double offset = 0.5;

void Robot::Move(int dir_front, int dir_back)
{
  int used_sensor = dir_front;
  double pre_dist = distanceSensor.GetDistance(dir_front);
  if (pre_dist == -1) 
  {
    pre_dist = distanceSensor.GetDistance(dir_back);
    used_sensor = dir_back;
  }

  double moved_dist = 0;
  while (abs(moved_dist - 30) >= offset){
    drive.Move(0.7);
    double new_dist = distanceSensor.GetDistance(used_sensor);
    moved_dist = abs(new_dist - pre_dist);
    gyro.Update();
    distanceSensor.Update();
    distanceSensor.Debug();
    Serial.println(moved_dist);
  }

  drive.Break();
  gyro.Update();
  distanceSensor.Update();
  distanceSensor.Debug();
}

void Robot::Start()
{
//   Tile maze[60][60];
//   facing = front;
//   Vector start_pos = Vector(30, 30);

  Move(1 + front, 1 + back);


  while(true)
  {


    gyro.Update();
    // colorSensor.Update();
    distanceSensor.Update();
    Serial.println(gyro.GetYaw());
    distanceSensor.Debug();
    // colorSensor.Debug();

    delay(100);
  }
}