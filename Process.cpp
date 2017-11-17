#include <string>
#include "Process.h"

using namespace std;

//Process.cpp is the constructor for the header file. It initializes all the values to 0

Process::Process()
{
	ProcessName = "";
	ProcessID = 0;
	sub = 0;
	StartTime = 0;
	EndTime = 0;
	CPUtimer = 0;
	IOtimer = 0;
	CPUtotal = 0;
	IOtotal = 0;
	CPUcount = 0;
	IOcount = 0;

	for(int i = 0; i < ARRAY_SIZE; i++){
		array[i] = 0;
	}
}
