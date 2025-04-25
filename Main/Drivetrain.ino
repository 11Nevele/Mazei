void InitDrive()
{

    Serial.println("Adafruit Motorshield v2 - DC Motor test!");

    if (!AFMS.begin()) 
    {         // create with the default frequency 1.6KHz
    // if (!AFMS.begin(1000)) {  // OR with a different frequency, say 1KHz
      Serial.println("Could not find Motor Shield. Check wiring.");
      //while(true);
    }
    
    Serial.println("Motor Shield found.");
    FR = AFMS.getMotor(3);
    BR = AFMS.getMotor(4);
    BL = AFMS.getMotor(2);
    FL = AFMS.getMotor(1);
}
void SetVelocity(Adafruit_DCMotor* m_Motor, double spd)
{
  if(spd > 0)
    m_Motor->run(FORWARD);
  else if(spd < 0)
    m_Motor->run(BACKWARD), spd = -spd;
  else
    m_Motor->run(RELEASE);
  m_Motor->setSpeed(spd*255.0);
}
  void Move(double spd)
  {

    SetVelocity(FL, spd);
    SetVelocity(BL, spd);
    SetVelocity(FR, spd);
    SetVelocity(BR, spd);
  }

  void Turn(double spd)
  {
    SetVelocity(FL, spd);
    SetVelocity(BL, spd);
    SetVelocity(FR, -spd);
    SetVelocity(BR, -spd);
  }

  void Break()
  {
    Move(-0.2);
    delay(100);
    SetVelocity(FL, 0);
    SetVelocity(BL, 0);
    SetVelocity(FR, 0);
    SetVelocity(BR, 0);
  }