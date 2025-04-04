

#include<Wire.h>

#include <Adafruit_MotorShield.h>

// Or, create it with a different I2C address (say for stacking)
// Adafruit_MotorShield AFMS = Adafruit_MotorShield(0x61);

// Select which 'port' M1, M2, M3 or M4. In this case, M1
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