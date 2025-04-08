#ifndef CAMERA_H
#define CAMERA_H
class Camera
{
  public:
  Camera(){};
  Camera(int, int, int, int);
  int GetColor();
  int GetLetter();
  private:
  int color1, color2, letter1, letter2; 
};
#endif