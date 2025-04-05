#include "PID.h"
#include <Arduino.h>
PID::PID(double nkp,double nki,double nkd)
{
    currentTime = millis();
    previousTime = millis();
    delta = 0;
    previousError = 0;
    cumError = 0;
    rateError = 0;
    kp = nkp;
    ki = nki;
    kd = nkd;
}

double PID:: GetPID(double error)
{
    currentTime = millis();
    
    rateError = (error - previousError);
    if(fabs(error) < 10)
            cumError += error;
        if ((error>0 && previousError<0)||(error<0 && previousError>0))
            cumError = 0; 
    double out = error * kp + cumError * ki + rateError * kd;
    previousTime = currentTime;
    previousError = error;
    return out;
    
}