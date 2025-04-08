#ifndef CAMERA_H
#define CAMERA_H
class Camera
{
  public:
  Camera(){};
  Camera(int, int, int);
  int GetVictim();
  private:
  int p1 = 0, p2 = 0, p3 = 0;
};
#endif