#include<Wire.h>
#include <Adafruit_MotorShield.h>
#include "Drivetrain.h"
#include "Robot.h"


void  setup()
{
  
  
  Serial.begin(115200);
  while(!Serial);
  Wire.begin();
  Wire.setClock(400000);
  delay(100);
  Robot robot;
  robot.Start();
  
}
void  loop()
{

}