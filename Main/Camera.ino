#include "Camera.h"
Camera::Camera(uint8_t c1, uint8_t c2, uint8_t l1, uint8_t l2)
{
  color1 = c1, color2 = c2, letter1 = l1, letter2 = l2;
  pinMode(color1, INPUT);
  pinMode(color2, INPUT);
  pinMode(letter1, INPUT);
  pinMode(letter2, INPUT);
}

int Camera::GetColor()
{
  int t= digitalRead(color1) + digitalRead(color2) * 2;
  return t;
}

int Camera::GetLetter()
{
  int t= digitalRead(letter1) + digitalRead(letter2) * 2;
  return t;
}