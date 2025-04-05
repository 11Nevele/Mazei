#ifndef PID_H
#define PID_H

class PID
{
    public:
    double currentTime, previousTime, delta;
    double previousError;
    double cumError;
    double rateError;
    double kp, ki, kd;
    PID(double, double , double );
    double GetPID(double);
    
  
};
#endif