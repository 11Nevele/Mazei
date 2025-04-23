#include<Wire.h>
#include <Adafruit_MotorShield.h>
#include "Drivetrain.h"
#include "Robot.h"
#include "Tile.hpp"
#include "Camera.h"
void  setup()
{
  
  
  Serial.begin(115200);
  Serial1.begin(115200);
  Serial2.begin(115200);
  while(!Serial);
  while(!Serial1);
  while(!Serial2);

  attachInterrupt(digitalPinToInterrupt(2), SetVictumFoundL, RISING);
  attachInterrupt(digitalPinToInterrupt(3), SetVictumFoundR, RISING);


  Wire.begin();
  Wire.setClock(400000);
  delay(100);
  Robot robot;

  robot.Start();
  
}
void  loop()
{

}