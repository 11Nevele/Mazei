#ifndef COLORSENSOR_HPP
#define COLORSENSOR_HPP
#include "Color.hpp"

class ColorSensor
{
  public:
  ColorSensor(uint8_t s0, uint8_t s1, uint8_t s2, uint8_t s3, uint8_t out) 
  {
    this->s0 = s0, this->s1 = s1, this->s2 = s2, this->s3 = s3, this->out = out;

    pinMode(s0,OUTPUT);     //pin modes
    pinMode(s1,OUTPUT);
    pinMode(s2,OUTPUT);
    pinMode(s3,OUTPUT);
    pinMode(out,INPUT);

    digitalWrite(s0,HIGH); //Putting S0/S1 on HIGH/HIGH levels   means the output frequency scalling is at 100% (recommended)
    digitalWrite(s1,HIGH);   //LOW/LOW is off HIGH/LOW is 20% and LOW/HIGH is  2%
    
  }


  int getColor()
  {
    return curColor;
  }
  void Debug()
  {
    Serial.print("red:");
    Serial.print(Red);
    Serial.print("\tgreen:");
    Serial.print(Green);
    Serial.print("\tBlue:");
    Serial.println(Blue);
    Serial.print("[DEBUG]::Cur color = ");
    if(curColor == red)
      Serial.println("RED");
    if(curColor == blue)
      Serial.println("BLUE");
    if(curColor == black)
      Serial.println("BLACK");
    if(curColor == white)
      Serial.println("WHITE");
    if(curColor == unknown)
      Serial.println("UNKNOWN");

  }
  void Update()
  {
    GetColors();                                     //Execute the GetColors function   to get the value of each RGB color
                                                    //Depending   of the RGB values given by the sensor we can define the color and displays it on   the monitor
    
    if (Red <=30 && Green <=30 && Blue <=30)         //If the values   are low it's likely the white color (all the colors are present)
        curColor = white;                   
        
    // else if (Red<Blue && Red<=Green && Red<30)      // if   Red value is the lowest one and smaller thant 23 it's likely Red
    //   curColor = red;

    else if (Blue<Green && Blue<Red && Blue<30)    //Same thing for Blue
       curColor = blue;

    else if (Red >=30 && Green >=30 && Blue >=30)        //Green it was a little tricky,   you can do it using the same method as above (the lowest), but here I used a reflective   object
      curColor = black;                  //which means the   blue value is very low too, so I decided to check the difference between green and   blue and see if it's acceptable

    else
      curColor = unknown;                //if the color is not recognized, you can add as many as you want
    
    
  }

  private:
  Color curColor = white;
  int Red = 0, Blue = 0, Green = 0;
  uint8_t s0,s1,s2,s3,out;
  void GetColors()  
  {    
    digitalWrite(s2, LOW);                                           //S2/S3 levels define which set   of photodiodes we are using LOW/LOW is for RED LOW/HIGH is for Blue and HIGH/HIGH   is for green 
    digitalWrite(s3, LOW);                                           
    Red = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);       //here we wait   until "out" go LOW, we start measuring the duration and stops when "out" is   HIGH again, if you have trouble with this expression check the bottom of the code
 
    digitalWrite(s3, HIGH);                                         //Here   we select the other color (set of photodiodes) and measure the other colors value   using the same techinque
    Blue = pulseIn(out, digitalRead(out) == HIGH ? LOW   : HIGH);
  
    digitalWrite(s2, HIGH);  
    Green = pulseIn(out,   digitalRead(out) == HIGH ? LOW : HIGH);
 
  }

};

#endif