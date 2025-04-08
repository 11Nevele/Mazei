#include "Drivetrain.h"
Drivetrain::Drivetrain():AFMS(0x62)
{

    Serial.println("Adafruit Motorshield v2 - DC Motor test!");

    if (!AFMS.begin()) 
    {         // create with the default frequency 1.6KHz
    // if (!AFMS.begin(1000)) {  // OR with a different frequency, say 1KHz
      Serial.println("Could not find Motor Shield. Check wiring.");
      //while(true);
    }
    
    Serial.println("Motor Shield found.");
    FR.Init(AFMS, 3);
    BR.Init(AFMS, 4);
    BL.Init(AFMS, 2);
    FL.Init(AFMS, 1);
}
  void Drivetrain::Move(double spd)
  {

    FL.SetVelocity(spd);
    BL.SetVelocity(spd);
    FR.SetVelocity(spd);
    BR.SetVelocity(spd);
  }

  void Drivetrain::Turn(double spd)
  {
    FL.SetVelocity(spd);
    BL.SetVelocity(spd);
    FR.SetVelocity(-spd);
    BR.SetVelocity(-spd);
  }

  void Drivetrain::Break()
  {
    Move(-0.2);
    delay(100);
    FL.SetVelocity(0);
    BL.SetVelocity(0);
    FR.SetVelocity(0);
    BR.SetVelocity(0);
  }