#include "pid.h"
#define dt 0.1;

double PID::getPID(double error)
{
	double output;
	double timeChange = dt;
	kpTerm = kp*error;
	
	/*Compute and bound integral*/
	errSum += (error*timeChange);
	kiTerm = errSum * ki;
	if (kiTerm>iMax)
	{
		kiTerm = iMax;
	}
	else if (kiTerm < -iMax)
	{
		kiTerm = -iMax;
	}
	
	kdTerm = (error - lastErr) / timeChange;
	
	output = kpTerm+kiTerm+kdTerm;
	lastErr = error;
	
	return output;
}

PID::PID()
{
	kp =0; ki =0; kd = 0;
}

void PID::Compute(void)
{
   /*How long since we last calculated*/
   double timeChange = dt;
  
   /*Compute all the working error variables*/
   double error = Setpoint - Input;
   errSum += (error * timeChange);
   double dErr = (error - lastErr) / timeChange;
  
   /*Compute PID Output*/
   Output = kp * error + ki * errSum + kd * dErr;
  
   /*Remember some variables for next time*/
   lastErr = error;
}
  
void PID::SetTunings(double Kp, double Ki, double Kd)
{
   kp = Kp;
   ki = Ki;
   kd = Kd;
}

void PID::resetI(void)
{
	kiTerm = 0;
	errSum = 0;
}

void PID::setImax(double imax)
{
	iMax = imax;
}
