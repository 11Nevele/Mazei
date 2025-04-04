#ifndef GYRO_H
#define GYRO_H


  public:
  Gyro();
  void Update();
  double GetYaw();
  double GetPitch();
  double GetRoll();


  private:
  double yaw, pitch, roll;
  const int CMPS12=0x60;
};

#endif