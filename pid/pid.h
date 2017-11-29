/*Keith Conley
 * USM
 * Fall 2017
 * */

#ifndef pid_h
#define pid_h

class PID
{
	public:
	PID();

	void SetTunings(double Kp, double Ki, double Kd);
	void setImax(double imax);
	void resetI(void);
	double getPID(double error);
	
	private:
	double errSum; //used as accumulated error for kiTerm 
	double lastErr;
	double kp, ki, kd;
	double kpTerm, kiTerm, kdTerm; //save individual output pieces
	double iMax;
};
#endif
