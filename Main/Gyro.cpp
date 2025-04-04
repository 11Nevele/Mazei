
#include "Gyro.h"

Gyro::Gyro()
{
  yaw = 0, pitch = 0, roll = 0;
}

double Gyro::GetYaw()
{
  return yaw;
}

double Gyro::GetPitch()
{
  return pitch;
}

double Gyro::GetRoll()
{
  return roll;
}

void Gyro::Update()
{
  Wire.beginTransmission(CMPS12);  
  Wire.write(0X02);                     
  Wire.endTransmission(false);
  Wire.requestFrom(CMPS12,4);
  yaw=(int16_t)(Wire.read()<<8|Wire.read())/10.00; //Two bytes Yaw in range of (0 to 359 degrees) 
  pitch=((int8_t)Wire.read()); // One byte Pitch in range of (-90 to 90 degrees)
  roll=((int8_t)Wire.read()); // One byte Roll in range of (-90 to 90 degrees)        
  
  Wire.beginTransmission(CMPS12);  
  Wire.write(0x1C);                     
  Wire.endTransmission(false);
}