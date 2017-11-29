/*Keith Conley
 * USM
 * Fall 2017
 * */

#include "pid.h"

/*500hz*/
#define dt 0.01

double PID::getPID(double error)
{
	double output;
	kpTerm = kp*error;
	
	/*Compute and bound integral*/
	errSum += (error*dt);
	kiTerm = errSum * ki;
	if (kiTerm>iMax)
	{
		kiTerm = iMax;
	}
	else if (kiTerm < -iMax)
	{
		kiTerm = -iMax;
	}
	
	kdTerm = (error - lastErr) / dt;
	
	output = kpTerm+kiTerm+kdTerm;
	lastErr = error;
	
	return output;
}

PID::PID()
{
	kp =0; ki =0; kd = 0;

	kpTerm = 0;
	kiTerm = 0;
	kdTerm=0;

	errSum = 0;
	lastErr = 0;

	iMax = 0;
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
