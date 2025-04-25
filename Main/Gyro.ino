

void InitGyro()
{
  
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
void Update()
{
  Wire.beginTransmission(CMPS12);  
  Wire.write(0X02);                     
  Wire.endTransmission(false);
  Wire.requestFrom(CMPS12,4);
  yaw=(int16_t)(Wire.read()<<8|Wire.read())/10.00; //Two bytes Yaw in range of (0 to 359 degrees) 
  pitch=((int8_t)Wire.read()); // One byte Pitch in range of (-90 to 90 degrees)
  roll=((int8_t)Wire.read()); // One byte Roll in range of (-90 to 90 degrees)        
  
}
double GetYaw()
{
  Update();
  double tmp  = (yaw + offset + 360);
  if(tmp >= 360)
    tmp -= 360;
  return tmp;
}

double GetPitch()
{
  Update();
  return pitch;
}

double GetRoll()
{
  Update();
  return roll;
}

