#include <iostream>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include "pid/pid.h"

long long int tim = 0;

void createPidTim(void);
void printTimHandle();
void processDecay();

void pidHandler(int signum);

/*variables for output values*/
double processVariable = 100;
void transducerOutput(double output);
#define outputMAX 100

/*PID Variables*/
PID myPID;
double pidOut;
#define kp 100
#define ki 1
#define kd 100

double setPoint;

int main(void)
{
	myPID.SetTunings(kp, ki, kd);
	myPID.setImax(1000.00);
	setPoint = 50000;

	createPidTim();

	while(1)
	{}

	return 0;
}

void pidHandler(int signum)
{
	++tim;

	if (tim%2==0)
	{
		processDecay();
		transducerOutput(pidOut);
	}
	if (tim%4==0)
	{
		pidOut = myPID.getPID(setPoint-processVariable);
		if (pidOut>outputMAX)
		{
			pidOut=outputMAX;
		}
	}
	if (tim%8==0)
	{
		printTimHandle();
	}
}

void createPidTim(void)
{
	struct sigaction sa;
	struct itimerval timer;

	/* Install timer_handler as the signal handler for SIGVTALRM. */
	memset (&sa, 0, sizeof (sa));
	sa.sa_handler = &pidHandler;
	sigaction (SIGVTALRM, &sa, NULL);

	/* Configure the timer to expire after 100 msec... */
	timer.it_value.tv_sec = 0;
	timer.it_value.tv_usec = 50000;
	/* ... and every 250 msec after that. */
	timer.it_interval.tv_sec = 0;
	timer.it_interval.tv_usec = 50000;
	/* Start a virtual timer. It counts down whenever this process is
	   executing. */
	setitimer (ITIMER_VIRTUAL, &timer, NULL);
}

void transducerOutput(double output)
{
	processVariable+=1*output;
}

void processDecay()
{
	processVariable = processVariable-0.001;
}

void printTimHandle()
{
	std::cout<<"Process Variable is: "<<processVariable <<" Setpoint is: " << setPoint<<'\n';
}