#include "Drivetrain.h"
Drivetrain::Drivetrain()
{
    AFMS = Adafruit_MotorShield();
    Serial.println("Adafruit Motorshield v2 - DC Motor test!");

    if (!AFMS.begin()) 
    {         // create with the default frequency 1.6KHz
    // if (!AFMS.begin(1000)) {  // OR with a different frequency, say 1KHz
      Serial.println("Could not find Motor Shield. Check wiring.");
      //while(true);
    }
    
    Serial.println("Motor Shield found.");
    FL.Init(AFMS, 1);
    FR.Init(AFMS, 2);
    BL.Init(AFMS, 3);
    BR.Init(AFMS, 4);
}
  void Drivetrain::Move(double spd)
  {

    FL.SetVelocity(spd);
    BL.SetVelocity(spd);
    FR.SetVelocity(spd);
    BR.SetVelocity(spd);
  }