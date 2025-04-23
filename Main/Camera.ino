#include "Camera.h"

void SetVictumFoundL()
{
  Serial.println("Victim Found");
  victimFoundL = true;
}
void SetVictumFoundR()
{
  Serial.println("Victim Found");
  victimFoundR = true;
}
char receiveVictimInfoCamL() {
  // TODO: is Serial1 connected to CamL? 
  // receive victim information when a victim is found

  while (Serial1.available() == 0) {} // wait for RT1062's report
  
  char*buf = new char[1];
  size_t t = Serial1.readBytes(buf, 1); 
  Serial.print("OpenMV: ");
  
  Serial.println(buf);

  // Notify the OpenMV camera
  //Serial1.print("Received");
  victimFoundL = false; 
  return buf[0];
}

char receiveVictimInfoCamR() {
  // TODO: is Serial1 connected to CamL? 
  // receive victim information when a victim is found

  while (Serial2.available() == 0) {} // wait for RT1062's report
  
  char* buf = new char[1];

  size_t t = Serial2.readBytes(buf, 1); 
  Serial.print("OpenMV: ");
  
  Serial.println(buf);

  // Notify the OpenMV camera
  //Serial1.print("Received");
  victimFoundR = false; 

  return buf[0];
}
