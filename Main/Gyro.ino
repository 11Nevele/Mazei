
#include "Gyro.h"

Gyro::Gyro()
{
  yaw = 0, pitch = 0, roll = 0;
  delay(1000);
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

  offset = -yaw;
}

double Gyro::GetYaw()
{
  Update();
  double tmp  = (yaw + offset + 360);
  if(tmp >= 360)
    tmp -= 360;
  return tmp;
}

double Gyro::GetPitch()
{
  Update();
  return pitch;
}

double Gyro::GetRoll()
{
  Update();
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