#include "PID.h"
#include <Arduino.h>

// Constructor for the PID class
PID::PID(double nkp, double nki, double nkd, double kiActiveDis)
{
    currentTime = millis();        // Initialize current time in milliseconds
    previousTime = millis();       // Initialize previous time in milliseconds
    delta = 0;                     // Not used in this snippet, possibly for future time delta
    previousError = 0;             // Stores the previous error value
    cumError = 0;                  // Cumulative error (used for integral term)
    rateError = 0;                 // Rate of change of error (used for derivative term)
    
    // Set PID constants
    kp = nkp;                      // Proportional gain
    ki = nki;                      // Integral gain
    kd = nkd;                      // Derivative gain

    // Distance within which the integral term is active
    this->kiActiveDis = kiActiveDis;
}

// Method to calculate the PID output based on the current error
double PID::GetPID(double error, bool useKP)
{
    currentTime = millis(); // Update current time

    // Calculate derivative (rate) of error
    rateError = (error - previousError);

    // Only accumulate error if within kiActiveDis range or if useKP flag is true
    if (fabs(error) < kiActiveDis || useKP)
        cumError += error;

    // Reset cumulative error if the error sign has changed (crossed zero)
    if ((error > 0 && previousError < 0) || (error < 0 && previousError > 0))
        cumError = 0;

    // Calculate PID output using the formula:
    // P = kp * error
    // I = ki * cumError
    // D = kd * rateError
    double out = error * kp + cumError * ki + rateError * kd;

    // Update previous values for next iteration
    previousTime = currentTime;
    previousError = error;

    return out; // Return the PID control value
}