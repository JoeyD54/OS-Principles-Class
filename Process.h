#include <string>
#include "Constants.h"

using namespace std;

#ifndef PROCESS_H
#define PROCESS_H

/*
//Class for the input from the file
class Process{
	public:
		string Command;				//Holder for the command letter
		int ProcessID;				//int for process id
		int Size;				//Int for size of needed storage
		string BlockID;				//Program name

		Process();
	private:

};
*/

//Class for the in use process
class InUse{
	public:
		int Address;				//Address of InUse item
		int Size;				//Size of InUse item

		InUse();				//Class Constructor
	private:

};


//Class for available memory
class Avail{
	public:
		int OneMBAdd;				//Int to hold OneMB Address
		int OneMB;				//Int to hold 1 megatbyte

		int FirstTwoAdd;			//First 2 MB block Address
		int FirstTwo;				//First 2 MB block

		int SecondTwoAdd;			//Second 2 MB block Address
		int SecondTwo;				//Second 2 MB block

		int FirstFourAdd;			//First 4 MB block Address
		int FirstFour;				//First 4 MB block

		int SecondFourAdd;			//Second 4 MB block Address
		int SecondFour;				//Second 4 MB block

		Avail();				//Class Constructor
	private:
};


#endif

