#include "Robot.h"
#include "RobotConfig.h"
#include "Tile.hpp"
#include "Vector.hpp"

Robot::Robot():
//rightCamera(rightCamerac1, rightCameral1, rightCameral2),

//drive(),
//gyro(),
//colorSensor(colorS0, colorS1, colorS2, colorS3, colorOut),
distanceSensor()
{
  pinMode(ledPort, OUTPUT);
  //Servo port = 47
  servo.attach(servoPort);
  servo.write(50);
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

void Robot::CheckVictum(int &vic)
{
  int t = rightCamera.GetVictim();
  distanceSensor.Update();
  if(t != 0&& !maze[r][c].GetVisited() && distanceSensor.GetDistance(right) < 200 && vic == 0)
    vic = t;

  Serial.println(t);
}

double const MOVEMENT_ERROR = 10;

static bool Robot::CheckMovementFinished(double target, double cur, double rate)
{
    bool ucRange = fabs(target - cur) < MOVEMENT_ERROR;
    //bool rateRange = fabs(rate) < ROTATION_RATE_ERROR;
    return ucRange ;
}

void Robot::MovePID(double dist, double maxSpeed, double time)
{
    double kp = 0.005, ki = 0.01, kd = 0.0;    
    PID pid(kp, ki,kd, 90);

    distanceSensor.Update();
    int used_sensor = front;
    double curDist = 0;
    double baseDist = distanceSensor.GetDistance(used_sensor);
    if (baseDist == -1){
      baseDist = distanceSensor.GetDistance(back);
      used_sensor = back;
      Serial.println("HI");
    }

    double st = millis();
    double waitTime = 1200; 

    delay(10);
    while(!CheckMovementFinished(dist, curDist, pid.rateError))
    {        
        distanceSensor.Update();
        curDist = abs(baseDist - distanceSensor.GetDistance(used_sensor));
        double curError = dist - curDist;

        double out = pid.GetPID(curError);

        if(out > maxSpeed) out = maxSpeed;
        else if(out < -maxSpeed) out = -maxSpeed;
        Serial.print(curError);
        Serial.print("\t");
        Serial.println(curDist);

        drive.Move(out);
        delay(5);
    }
    
    drive.Move(0);
    gyro.Update();
    distanceSensor.Update();
    delay(100);
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
  PID pid(kp, ki,kd, 10);
   
  double curRotation  = gyro.GetYaw();
  double st = millis();
  double waitTime = 1500;

  int vic = 0;
  delay(10);
  while(!CheckRotationFinished(target, curRotation, pid.rateError))
  {        
      CheckVictum(vic);
      curRotation = gyro.GetYaw();
      double curError = AngleDif(curRotation, target);
      
      double out = pid.GetPID(curError, st + waitTime < millis());

      if(out > maxSpeed) out = maxSpeed;
      else if(out < -maxSpeed) out = -maxSpeed;
    
      drive.Turn(out);
      delay(5);
  }
  drive.Turn(0);
  delay(100);  
  if(vic != 0)
  {
    Flash();
  }


  
}


// const double offset = 20;

/*
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
*/

void Robot::Start()
{ 
  facing = front;
  int dir[4][2]{{0, -1},{1, 0}, {0, -1}, {-1, 0}};
  double rotation[4]{270, 0, 90, 180};int t=0;
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
    MovePID(300, 0.5, 1000);  
    r += dir[facing][0], c += dir[facing][1];
  }

  
}