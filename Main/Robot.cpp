#include "Robot.h"
#include "RobotConfig.h"
#include "Tile.hpp"
#include "Vector.hpp"
#include "Color.hpp"

Robot::Robot()://leftCamera(leftCamerac1, leftCamerac2, leftCameral1, leftCameral2), 
//rightCamera(leftCamerac1, leftCamerac2, leftCameral1, leftCameral2),
distanceSensor(),
drive(),
// gyro(),
colorSensor(colorS0, colorS1, colorS2, colorS3, colorOut)
//servo(),

{
  pinMode(ledPort, OUTPUT);
  //servo.attach(servoPort);

}


double const ROTATION_ERROR = 0.5, ROTATION_RATE_ERROR = 0.5; 

bool Robot::CheckRotationFinished(double target, double cur, double rate)
{
    bool ucRange = fabs(target - cur) < ROTATION_ERROR;
    bool rateRange = fabs(rate) < ROTATION_RATE_ERROR;
    return ucRange && rateRange ;
}
void Robot::CheckVictum()
{
  int c = leftCamera.GetColor();
  int l = leftCamera.GetLetter();
  Serial.println(c);
  Serial.println(l);
  //if((c > 0 || l > 0) && distanceSensor.GetDistance(left) <= 140)
  //{
    //digitalWrite(ledPort, HIGH);
    //delay(500);
    //digitalWrite(ledPort, LOW);
  //}
}

void Robot::Turn(double target, double maxSpeed = 0.5){
  double kp = 0.01, ki = 0.001, kd = 0; 
  PID pid(kp, ki,kd);
   
  double curRotation  = gyro.GetYaw();
  double st = millis();
  double waitTime = 1500;
  delay(10);
  while(!CheckRotationFinished(target, curRotation, pid.rateError))
  {        
      CheckVictum();
      curRotation = gyro.GetYaw();
      double curError = AngleDif(curRotation, target);
      
      double out = pid.GetPID(curError, st + waitTime < millis());

      if(out > maxSpeed) out = maxSpeed;
      else if(out < -maxSpeed) out = -maxSpeed;
      //Serial.print("Error: ");
      //Serial.print(curError);
      //Serial.print(" OUT: ");
      //Serial.println(out);
    
      drive.Turn(out);
      delay(10);
  }

  drive.Turn(0);
  delay(100);  
}

const double offset = 20;

void Robot::Move(double distance, double mxSpd)
{
  int used_sensor = front;
  distanceSensor.Update();
  double pre_dist = distanceSensor.GetDistance(front);


  double moved_dist = 0;

  drive.Move(0.2);
  while (moved_dist <= 300 - offset)
  {
    distanceSensor.Update();
    double new_dist = distanceSensor.GetDistance(used_sensor);
    moved_dist = abs(new_dist - pre_dist);
    CheckVictum();
    Serial.print("Previous Distance: ");
    Serial.print(pre_dist);
    Serial.print("Current Distance: ");
    Serial.print(new_dist);
    Serial.print("Moved Distance: ");
    Serial.println(moved_dist);
    delay(5);
  }

  drive.Break();
  gyro.Update();
  distanceSensor.Update();
  distanceSensor.Debug();
}

void Robot::Start()
{


  facing = front;
  int r = 15, c= 15;
  int dir[4][2]{{0, -1},{1, 0}, {0, -1}, {-1, 0}};
  double rotation[4]{270, 0, 90, 180};
  
  while (true){
    drive.Move(0.3);
    if (colorSensor.getColor() == black){
      drive.Move(-0.3);
      delay(1000);
    }
  }

  /*
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
    Turn(rotation[facing]);
    Move(300, 1);  
    r += dir[facing][0], c += dir[facing][1];
  }
  */
}