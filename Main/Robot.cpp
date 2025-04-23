#include "Robot.h"
#include "RobotConfig.h"
#include "Tile.hpp"
#include "Vector.hpp"
#include "Color.hpp"
#include "Camera.h"

Robot::Robot():distanceSensor(),drive(),gyro(),colorSensor(colorS0, colorS1, colorS2, colorS3, colorOut),servo()
{
  pinMode(ledPort, OUTPUT);
  servo.attach(servoPort);
}
void Robot::Swipe()
{
  servo.write(110);
  delay(1000);
  servo.write(50);
  delay(1000);
}
void Robot::Flash()
{
  digitalWrite(ledPort, HIGH);
  delay(500);
  digitalWrite(ledPort, LOW);
  delay(500);
}

void Robot::CheckVictum(char &vic)
{
  if(vic != 0)
    return;
  if(victimFoundL)
  { 
    vic = receiveVictimInfoCamL();
  }
  if(victimFoundR)
  {
    vic = receiveVictimInfoCamR();
  }

}
double const MOVEMENT_ERROR = 10;

bool Robot::CheckMovementFinished(double target, double cur, double rate)
{
    bool ucRange = fabs(target - cur) < MOVEMENT_ERROR;
    //bool rateRange = fabs(rate) < ROTATION_RATE_ERROR;
    return ucRange ;
}

void Robot::MovePID(double dist, double maxSpeed, double time, double direction)
{
    double kp = 0.003, ki = 0.003, kd = 0.0;    
    PID pid(kp, ki,kd, 90);
    char vic = 0;
    distanceSensor.Update();
    int used_sensor = front;
    double curDist = 0;
    double baseDist = distanceSensor.GetDistance(used_sensor);
    if (baseDist == -1 || (distanceSensor.GetDistance(back) < baseDist && distanceSensor.GetDistance(back) != -1))
    {
      baseDist = distanceSensor.GetDistance(back);
      used_sensor = back;
      Serial.println("HI");
    }
    
    Serial.println("Start moving");
    double st = millis();
    double waitTime = 5000; 

    delay(10);
    while(!CheckMovementFinished(dist, curDist, pid.rateError))
    {   
        distanceSensor.Update();
        colorSensor.Update();
        CheckVictum(vic);
        curDist = abs(baseDist - distanceSensor.GetDistance(used_sensor));
        double curError = dist - curDist;
        if (colorSensor.getColor() == black && direction != -1){
          drive.Break();
          Serial.println("Reverse");
          delay(500);
          distanceSensor.Update();
          curDist = abs(baseDist - distanceSensor.GetDistance(used_sensor));
          MovePID(curDist, 0.3, 0, -1);
          facing = (facing + 2) % 4;
          Turn(rotation[facing], 0.5);

          break;
        }

        if (gyro.GetPitch() > 15){
          drive.Move(0.4);
          delay(2000);
          break;
        }

        if (gyro.GetPitch() < -10){
          drive.Move(0.15);
          delay(4000);
          break;
        }
        

        double out = pid.GetPID(curError);

        if(out > maxSpeed) out = maxSpeed;
        else if(out < -maxSpeed) out = -maxSpeed;
        if (out < 0) out *= 0.4;
        Serial.print(distanceSensor.GetDistance(used_sensor));
        Serial.print("\t");
        Serial.print("Cur Dist: ");
        Serial.println(curDist);

        drive.Move(out * direction);

    }
    
    switch(vic)
    {
      case 'R':
        Flash();
        Swipe();
        Swipe();
        break;
      case 'G':
        Flash();
        break;
      case 'Y':
        Flash();
        Swipe();
        break;
      case 'H':
        Flash();
        Swipe();
        Swipe();
        break;
      case 'S':
        Flash();
        break;
      case 'U':
        Flash();
        Swipe();
        break;  
    }

    drive.Move(0);
    gyro.Update();
    distanceSensor.Update();
    delay(100);
}


double const ROTATION_ERROR = 2, ROTATION_RATE_ERROR = 10; 

bool Robot::CheckRotationFinished(double target, double cur, double rate)
{
    bool ucRange = fabs(target - cur) < ROTATION_ERROR;
    bool rateRange = fabs(rate) < ROTATION_RATE_ERROR;
    return ucRange && rateRange ;
}

void Robot::Turn(double target, double maxSpeed = 0.5)
{
  double kp = 0.010, ki = 0.0015, kd = 0.0; 
  PID pid(kp, ki,kd, 10);
   
  double curRotation  = gyro.GetYaw();
  double st = millis();
  double waitTime = 1500;
  delay(10);
  char vic = 0;
  while(!CheckRotationFinished(target, curRotation, pid.rateError))
  {        
      curRotation = gyro.GetYaw();
      CheckVictum(vic);
      double curError = AngleDif(curRotation, target);
      
      double out = pid.GetPID(curError, false);

      if(out > maxSpeed) out = maxSpeed;
      else if(out < -maxSpeed) out = -maxSpeed;
      Serial.print("Error: ");
      Serial.print(curError);
      Serial.print(" curRotation: ");
      Serial.println(gyro.GetYaw());
    
      drive.Turn(out);
  }

  switch(vic)
  {
    case 'R':
      Flash();
      Swipe();
      Swipe();
      break;
    case 'G':
      Flash();
      break;
    case 'Y':
      Flash();
      Swipe();
      break;
    case 'H':
      Flash();
      Swipe();
      Swipe();
      break;
    case 'S':
      Flash();
      break;
    case 'U':
      Flash();
      Swipe();
      break;  
  }

  drive.Turn(0);
  delay(100);  
}


void Robot::Start()
{


  facing = front;
  int r = 30, c= 30;
  
  Serial.println("Start Robot");
  distanceSensor.Update();

  srand(colorSensor.Red * colorSensor.Green * colorSensor.Blue);
  // while(true)
  // {
  //   colorSensor.Update();
  //   colorSensor.Debug();
  //   delay(200);
  // }
  
  while(true)
  {    
    
    maze[r][c].SetVisited(true);
    bool wall[3]{}, visited[3]{};
    distanceSensor.Update();

    for(int i = 0; i < 3; ++i)
    {
      if(distanceSensor.GetDistance(i) <= 200 && distanceSensor.GetDistance(i) != -1)
        wall[i] = true;
      int ind = ((int)facing - 1 + i + 4) % 4; 
      int nr = r + dir[ind][0], nc = c + dir[ind][1];
      visited[i] = maze[nr][nc].GetVisited();
      Serial.print(wall[i]);
      Serial.print(visited[i]);
    }
    
    int candidates[3];
    int candidates2[3];
    int count = 0;
    int count2 = 0;

    // Collect unvisited (and optionally unblocked) indices
    for (int i = 0; i < 3; ++i)
    {
        if (!visited[i] && !wall[i]) // You can remove `!wall[i]` if you don't want to avoid walls
            candidates[count++] = i;
        if(!wall[i])
          candidates2[count2++] = i;
    }

    int choice;
    if (count > 0)
    {
        choice = candidates[rand() % count];
    }
    else if(count2 > 0)
    {
        // No unvisited options, pick randomly from all 0 to 2
        choice = candidates2[rand() % count2];
    }
    else
    {
      choice = -1;
    }
    choice -= 1;
    facing = (facing + choice + 4) % 4;
    colorSensor.Update();
    if(colorSensor.getColor() == blue)
    {
      Flash();
      delay(5000);
    }
    Turn(rotation[facing]);
    MovePID(300, 0.5, 1000, 1);  
    r += dir[facing][0], c += dir[facing][1];
  }
  
}