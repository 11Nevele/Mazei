#include<Wire.h>
#include <Adafruit_MotorShield.h>

// #include <Adafruit_Sensor.h>
#include <SparkFun_I2C_Mux_Arduino_Library.h>  
#include <Adafruit_VL53L0X.h>

#include "PID.h"


//Drivetrain things
Adafruit_DCMotor* FL, *FR, *BL, *BR;
Adafruit_MotorShield AFMS;


//Distance Sensor things
const int NUMBER_OF_SENSORS = 4;
int distances[4 + 1]{}; //1: left 2:front 3:right 4:back
Adafruit_VL53L0X** distanceSensor;
QWIICMUX myMux;

//color sensor
enum Color
{
  red, blue, green, white, black, unknown
};

Color curColor = white;
int Red = 0, Blue = 0, Green = 0;
uint8_t s0 = 29,s1 = 27,s2 = 25,s3 = 23,out = 31;

//gyro
int CMPS12 = 0x60;//address of gyro
double yaw = 0, pitch = 0, roll = 0;
double offset = 0;

//the degrees to turn to when facing
//                  W   N   E   S
double rotation[4]{270, 0, 90, 180};

int facing;
void  setup()
{
  Serial.begin(115200);
  while(!Serial);
  Wire.begin();
  Wire.setClock(400000);
  InitDrive();
  InitColorSensor();
  InitGyro();
  InitDistanceSensor();

  //0 = west 1 = north 2 = east 3 = south
  //the facing direction of the robot is defined as north
  facing = 1;
  
  UpdateDistanceSensor();
  UpdateColorSensor();

  //use color sensor reading as rand seed
  srand(Red * Green * Blue);
}


//caculate the smallest dif between to angles
double AngleDif(double from, double to)
  {
    double t = to - from;
    if(t > 180)
      t = t - 360;
    if(t < -180)
      t = t + 360;
    return t;
  }

double const ROTATION_ERROR = 2, ROTATION_RATE_ERROR = 10; 

bool CheckRotationFinished(double target, double cur, double rate)
{
  //allows 2 degrees of error
    bool ucRange = fabs(target - cur) < ROTATION_ERROR;
  //the robot must be moving slowly
    bool rateRange = fabs(rate) < ROTATION_RATE_ERROR;
    return ucRange && rateRange ;
}

void TurnPID(double target, double maxSpeed = 0.5)
{
  double kp = 0.010, ki = 0.0015, kd = 0.0; 
  PID pid(kp, ki,kd, 10);
   
  double curRotation  = GetYaw();
  delay(10);
  while(!CheckRotationFinished(target, curRotation, pid.rateError))
  {        
      curRotation = GetYaw();
      double curError = AngleDif(curRotation, target);
      
      double out = pid.GetPID(curError, false);

      if(out > maxSpeed) out = maxSpeed;
      else if(out < -maxSpeed) out = -maxSpeed;

      Serial.print("Error: ");
      Serial.print(curError);
      Serial.print(" curRotation: ");
      Serial.println(curRotation);
    
      Turn(out);
  }

  Turn(0);
  delay(100);  
}


int MOVEMENT_ERROR = 10;
bool CheckMovementFinished(double target, double cur, double rate)
{
    bool ucRange = fabs(target - cur) < MOVEMENT_ERROR;
    //bool rateRange = fabs(rate) < ROTATION_RATE_ERROR;
    return ucRange ;
}
void MovePID(double dist, double maxSpeed, double time, double direction)
{
    double kp = 0.003, ki = 0.003, kd = 0.0;    
    PID pid(kp, ki,kd, 90);
    UpdateDistanceSensor();
    int used_sensor = 2;//use front sensor by default
    double curDist = 0;
    double baseDist = distances[used_sensor];//get current distance away from the wall

    //if the front wall is too far to see, use back sensor
    if (baseDist == -1 || (distances[4] < baseDist && distances[4] != -1))
    {
      baseDist = distances[4];
      used_sensor = 4;
      Serial.println("Back sensor used");
    }
    
    Serial.println("Start moving");

    delay(10);
    //while movement is not finished
    while(!CheckMovementFinished(dist, curDist, pid.rateError))
    {   
        UpdateDistanceSensor();
        UpdateColorSensor();
        //get the distance travelled
        curDist = abs(baseDist - distances[used_sensor]);

        //get distance that still need to be travelled
        double curError = dist - curDist;

        //if see black
        if (curColor == black && direction != -1)
        {
          Break();
          Serial.println("Reverse");
          delay(500);
          UpdateDistanceSensor();

          //move back
          curDist = abs(baseDist - distances[used_sensor]);
          MovePID(curDist, 0.3, 0, -1);
          
          //turn around
          facing = (facing + 2) % 4;
          TurnPID(rotation[facing], 0.5);

          break;
        }

        //use dead reconing on slope
        if (GetPitch() > 15){
          Move(0.4);
          delay(2000);
          break;
        }

        //slow down on down ramp
        if (GetPitch() < -10){
          Move(0.15);
          delay(4000);
          break;
        }
        
        //get PID, watch a videa to understand how PID work, or call me
        double out = pid.GetPID(curError);

        if(out > maxSpeed) out = maxSpeed;
        else if(out < -maxSpeed) out = -maxSpeed;
        if (out < 0) out *= 0.4;

        Serial.print(distances[used_sensor]);
        Serial.print("\t");
        Serial.print("Cur Dist: ");
        Serial.println(curDist);

        Move(out * direction);
    }
    
    
    //stop
    Move(0);
    delay(100);
}






void loop()
{
 
    //0 = left 1 = front 2 = right
    //record is there a in in these directions
    //ex wall[1] == true means there is a wall in the front
    bool wall[3]{};
    UpdateDistanceSensor();

    //directions that are avaiable
    int candidates[3];
    //the number of avaiable direction
    int count = 0;
    for(int i = 0; i < 3; ++i)
    {
      //if there is a wall in 200mm
      if(distances[i + 1] <= 200 && distances[i + 1] != -1)
        wall[i] = true;
      Serial.print(wall[i]);

      //is no wall, add to candidates
      if(!wall[i])
      {
        candidates[count++] = i;
      }
    }
    
    

    int choice;
    if (count > 0)
    {
      //randomly select a path
        choice = candidates[rand() % count];
    }
    else
    {
      //turn around
      choice = -1;
    }

    //update current facing, slightly hard to explain in comment, call me if you have to understand this
    choice -= 1;
    facing = (facing + choice + 4) % 4;

    UpdateColorSensor();
    if(curColor == blue)
    {
      delay(5000);
    }

    //turn to the desired direction
    TurnPID(rotation[facing]);
    //move forward a grid
    MovePID(300, 0.5, 1000, 1);  
  }