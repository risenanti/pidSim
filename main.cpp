#include <iostream>
#include <fstream>
#include "pid/pid.h"
using namespace std;

#define FILENAME "kpOut.txt"

#define outputMAX 1000

/*variables for output values*/
struct processValues
{
	double processVariable; /*starting value*/
	double pidOut;
	double setPoint;
	PID myPID;
};

void processDecay(processValues &inst);
void transducerOutput(processValues &inst);
void pidHandler(processValues &inst, std::ofstream &file);
void printTimHandle(long long int tim, processValues &inst, std::ofstream &file);

int main()
{
	/*PID Variables*/
	#define kp 18.00
	#define ki 0.00
	#define kd 0.00

	processValues instance;

	instance.setPoint = 500000;
	instance.processVariable = 100;

	instance.myPID.SetTunings(kp, ki, kd);
	instance.myPID.setImax(1000.00);

	/*File ops*/
	std::ofstream file;
	file.open(FILENAME, std::ofstream::out);

	while(1)
	{
		static long long int i = 0;
		++i;
		if (i>100000)
		{
			file.close();
			break;
		}
		pidHandler(instance, file);
	}

	return 0;
}

void transducerOutput(processValues &inst)
{
	inst.processVariable+=1*inst.pidOut;
}

void processDecay(processValues &inst)
{
	inst.processVariable = inst.processVariable-0.00001;
}

void printTimHandle(long long int tim, processValues &inst, std::ofstream &file)
{
	cout<< "TIME IS: "<<tim<<" Process Variable is: "<<inst.processVariable <<" Setpoint is: " << inst.setPoint<<'\n';
	file<<"TIME="<<tim<<" processVariable="<<inst.processVariable<<" Setpoint="<<inst.setPoint<<std::endl;
}

void pidHandler(processValues &inst, std::ofstream &file)
{
	static long long int tim = 0;
	tim++;

	if (tim%3==0)
	{
		processDecay(inst);
		transducerOutput(inst);
	}
	if (tim%4==0)
	{
		inst.pidOut = inst.myPID.getPID(inst.setPoint-inst.processVariable);
		if (inst.pidOut>outputMAX)
		{
			inst.pidOut=outputMAX;
		}
	}
	if (tim%8==0)
	{
		printTimHandle(tim, inst, file);
	}
}
