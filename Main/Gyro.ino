
#include "Gyro.h"

Gyro::Gyro()
{
  if (!mpu.begin()) 
  {
    Serial.println("Failed to find MPU6050 chip");
    while (1);
  }
  preTime = millis();
  delay(10);
  mpu.setAccelerometerRange(MPU6050_RANGE_2_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
  angleX = 0, angleY = 0, angleZ = 0;
}

void Gyro::Update()
{
  FetchData();
}

void Gyro::FetchData()
{
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  /* Print out the values */
  accX = a.acceleration.x;
  accY = a.acceleration.y;
  accZ = a.acceleration.z;

  gyroX = g.gyro.x * RADTODEGREE;
  gyroY = g.gyro.y * RADTODEGREE;
  gyroZ = g.gyro.z * RADTODEGREE;

  unsigned long curTime = millis();
  double dt = (double)(curTime - preTime) / 1000.0;
  angleX += gyroX * dt;
  angleY += gyroY * dt;
  angleZ += gyroZ * dt;
}