#include "Camera.h"
Camera::Camera(int p1, int p2, int p3)
{
  this->p1 = p1, this->p2 = p2, this->p3 = p3;
  pinMode(p1, INPUT);
  pinMode(p2, INPUT);
  pinMode(p3, INPUT);

}

int Camera::GetVictim()
{
  Serial.print("p1: ");
  Serial.print(digitalRead(p1));
  Serial.print(" p2: ");
  Serial.print(digitalRead(p2));
  Serial.print(" p3: ");
  Serial.println(digitalRead(p3));
  delay(100);
  int t = digitalRead(p1) + digitalRead(p2) * 2 + digitalRead(p3) * 4;
  return t;
}