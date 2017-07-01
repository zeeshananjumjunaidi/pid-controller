#include "PID.h"
#include <math.h>
#include <vector>
#include <ctime>
#include <iostream>

using namespace std;

PID::PID() { }

PID::~PID() {}

void PID::Init(double Kp_, double Ki_, double Kd_) {
    (*this).Kp=Kp_;
    (*this).Kd = Kd_;
    (*this).Ki=Ki_;
    p_error=0;
    i_error=0;
    d_error=0;
}

void PID::UpdateErrorP(double cte) {
    p_error = cte;
}

void PID::UpdateErrorPD(double cte) {
   d_error = cte - p_error;
    p_error = cte;
}

void PID::UpdateErrorPID(double cte) {
   d_error = cte - p_error;
    i_error += cte;
    p_error = cte;
}

//Not used
double PID::TotalError() {
  return -Kp * p_error;
}


