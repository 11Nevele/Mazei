#ifndef CAMERA_H
#define CAMERA_H
class Camera
{
  public:
  Camera(){};
  Camera(uint8_t, uint8_t, uint8_t, uint8_t);
  int GetColor();
  int GetLetter();
  private:
  uint8_t color1, color2, letter1, letter2; 
};
#endif