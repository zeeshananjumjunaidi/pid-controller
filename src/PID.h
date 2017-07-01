#ifndef PID_H
#define PID_H

class PID {
public:
  /*
  * Errors
  */
  double p_error;
  double i_error;
  double d_error;
  double prev_error;

  /*
  * Coefficients
  */ 
  double Kp;
  double Ki;
  double Kd;
  /*
  * Constructor
  */


  PID();

  /*
  * Destructor.
  */
  virtual ~PID();

  /*
  * Initialize PID.
  */
  void Init(double Kp_, double Ki_, double Kd_);

  /*
  * Update the PID error variables given cross track error.
  */
  void UpdateErrorP(double cte);
  void UpdateErrorPD(double cte);
  void UpdateErrorPID(double cte);
  
  /*
  * Calculate the total PID error.
  */
  double TotalError();
  
};

#endif /* PID_H */
