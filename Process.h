#include <string>
#include "Constants.h"

using namespace std;

#ifndef PROCESS_H
#define PROCESS_H


//Set up the process class

class Process{
public:
        string ProcessName;             //Process name holder
        int ProcessID;                  //Process ID holder
        int sub;                        //Array subscript
        int array[ARRAY_SIZE];          //Array as big as the array size constant
	int StartTime;			//Time a process starts
	int EndTime;			//Time a process ends
        int CPUtimer;                   //CPU burst timer
        int IOtimer;                    //IO timer
        int CPUtotal;                   //total CPU Time
        int IOtotal;                    //Total IO time
        int CPUcount;                   //CPU burst counter
        int IOcount;                    //IO counter

        Process();                      //class constructor
private:

};

#endif
