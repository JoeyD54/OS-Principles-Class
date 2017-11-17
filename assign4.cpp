#include <string.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <queue>
#include <sstream>
#include "Queue.h"
#include "Process.h"

using namespace std;

/*

Program: 4
Programmer: Joey Domino

Due Date: 10/12/15 11:59 pm

This program will simulate a round robin scheduling system as if on a single
CPU. The process, queue , and constants are split into their own cpp and header files.

*/


//Declare Prototype
bool Clear();
void EndProcess(Process * &);

//Create the queues and set global variables
Queue Entry;				//Queue for jobs not in cycle yet
Queue Ready;				//Queue for jobs waiting to be made actve
Queue io;				//Queue for jobs waiting for IO
Process * Active;			//Current active process
Process * IOActive;			//Current active IO process
int PNum = 101;				//Process number to come next
int NumInUse = 0;			//Process number not in entry and not killed
int timer = 0;				//Overal timer per process
bool IdleFlag = false;			//Flag to check if nothing is happening
int IdleTimer = 0;			//Timer for how long we're idle
int DeathCount = 0;			//Keep track of terminated processes
int i = 0;				//Used for any while or for loops



int main()
{

	cout << "\n\nWelcome to the CPU Round Robin Simulation! Get ready for information!\n\n";

	//Create initial variables to get file contents
	string line;
	string name;
	Process * A;			//Pointer to process class named A


	//Get contents and file and store them correctly

	ifstream MyFile ("data4.txt");				//Open file and get contents
	if(MyFile.is_open()){
		MyFile >> name;					//Get first item in file
		while(name != "STOPHERE"){			//Do loop until name holds STOPHERE
			A = new Process;			//Create space for new process
			A -> ProcessName = name;		//Put first item in name
			A -> ProcessID = PNum;			//Put Pnum into ProcessID for printing
			PNum++;					//Increment process number for next run
			for(i = 0; i < ARRAY_SIZE; i++){	//Fill the array with the rest
				MyFile >> A -> array[i];
			}
			Entry.push(A);				//Go to next line
			MyFile >> name;				//Get next process name
		}
	}
	MyFile.close();						//Close the file


//Files components should now be all within the Entry queue.
//Now move the items in the Entry to the Ready queue

	i = 0;							//Reset i to 0

	while(!Entry.IsEmpty() && i < IN_USE){			//While i is less than 5 and entry is not empty
		A = Entry.pop();				//Take process from entry
		Ready.push(A);					//Put process into ready queue
		NumInUse++;					//Increment in use count
		i++;						//Increment i
	}


//Ready queue should now be filled with 5 items at most
//Now we run through putting processes into the Active queue from the Ready

	int Burst;						//Initializing terms for loop
	int IOburst;

	while(timer < MAX_TIME && !Clear()){			//Check for all things being not empty
		if(timer % HOW_OFTEN == 0){			//print info if timer reaches limit
			cout << "Top of the main loop. The time is " << timer << "\n";
			if(Active == 0){			//If Active is empty
				cout << "Nothing is Active\n";
			}
			else{
				cout << Active -> ProcessID << " is Active\n";
			}
			if(IOActive == 0){			//if IOActive is empty
				cout << "Nothing is Active in IO\n";
			}
			else{
				cout << IOActive -> ProcessID << " is Active in IO\n";
			}
			cout << "Contents of Ready Queue:\n";
			Ready.PrintQ();				//Print contents of ready and IO queue

			cout << "Contents of IO Queue:\n";
			io.PrintQ();
			cout << "\n";
		}

		//Reload the active queue if the Active queue is empty

		if(Active == 0){
			if(!Ready.IsEmpty()){			//If there is things in ready queue
				Active = Ready.pop();		//Take 1 process
			}
			else if(!Entry.IsEmpty() && NumInUse < IN_USE){
					A = Entry.pop();		//Else take from entry queue
					A -> StartTime = timer;		//Store current time for printing
					NumInUse++;			//Increment processes in use

					//Signify that the item was moved

					cout << "Process " << A -> ProcessID << " has moved from Entry Queue to "
					     << "the Ready Queue. It then became active at " << timer << "\n\n";

					Ready.push(A);			//move process into Ready
					Active = Ready.pop();		//Take it from Ready and put it into Active
					Active -> CPUtimer++;		//Increment burst timer
				}
		}




		//All checks for Active being empty is completed
		//Now we check for bursts

		if(Active != 0){
			IdleFlag = false;			//Reset flag to false
			Burst = Active -> array[Active -> sub];	//Get the Burst from array subscript
			Active -> CPUcount++;			//Increment burst count
			Active -> CPUtimer++;			//Increment total CPU time

			if(Active -> CPUcount == Burst){	//if burst counter is size of burst, burst ended
				Active -> sub++;
				Burst = Active -> array[Active -> sub];  //Get new burst number

				if(Burst != 0){			//IO bursts occur on non 0 burst
					io.push(Active);	//Get next item
					Active -> CPUcount = 0; //Reset burst counter
					Active = 0;		//Reset Active
				}
				else{				//Otherwise, terminate and print info
					EndProcess(Active);	//End current active process
					Active = 0;		//Reset active
				}
			}
			else{
				if(Active -> CPUcount == TIME_SLICE){	//do time slice check
					Ready.push(Active);
					if(Burst == TIME_SLICE){
						Active -> CPUcount = 0;	//Reset counter if reached time slice
					}
					Active = 0;
				}
			}
			if(Entry.IsEmpty() && Ready.IsEmpty() && io.IsEmpty() && IOActive == 0){
				EndProcess(Active);	//End final process if the rest is empty
				Active = 0;
			}
		}
		else{ 					//Else Active is 0
			IdleTimer++;			//CPU is now idle
			if(!IdleFlag){			//if flag is true
				cout << "Active is 0 at " << timer << " and became idle!\n\n";
			}
			IdleFlag = true;		//Change flag
		}

		//Active has now been taken care of
		//Now we tend to IOactive

		if(IOActive == 0){				//If IO isn't active and is'nt empty, pop it
			if(!io.IsEmpty()){
				IOActive = io.pop();		//Remove process
				IOActive -> IOcount++;		//Increment IO burst counter
			}
		}
		if(IOActive != 0){
			IOburst = IOActive -> array[IOActive -> sub];	//Set io array sub to io burst
			IOActive -> IOcount++;
			IOActive -> IOtotal++;

			if(IOActive -> IOcount + IOburst == 0){			//End of burst
				Ready.push(IOActive);				//Get next item
				IOActive -> IOcount = 0;			//Reset counter
				IOActive -> sub++;

				if(IOActive -> array[IOActive -> sub] != 0){	//if IOsub is not 0
					IOActive -> CPUcount++;			//Increment burst count
				}

				IOActive = 0;			//Reset active
			}
		}

		timer++;					//Finally, increment the timer
	}


	//All the checks are done. All that is left now is to print the final data

	cout << "\nThe run is over!\n"
	     << "The time it took to finish is: " << timer << "\n"
	     << "Total idle time: " << IdleTimer << "\n"
	     << "Total terminated processes: " << DeathCount << "\n"
	     << "\nContents of Entry Queue: \n";

	Entry.PrintQ();

	cout << "\nContents of Ready Queue: \n";

	Ready.PrintQ();

	cout << "\nContents of IO Queue: \n";

	io.PrintQ();

	cout << "\nScheduling complete. Toodles!\n\n";

	return 0;
}


/*

Function: Clear

This function exists only to save space up above. It checks for active, ioactive, and all 3 queues to be empty

return: 1 or 0

*/

bool Clear()
{
	return (io.IsEmpty() && Ready.IsEmpty() && Entry.IsEmpty() && Active == 0 && IOActive == 0);
}


void EndProcess(Process * & X)
{
	int Wait = 0;		//Initialize variable

	X -> EndTime = timer;	//Set end time

	cout << "\nProcess " << X -> ProcessID << " has ended.\n"
	     << "Process Name: " << X -> ProcessName << "\n"
	     << "Process Started at " << X -> StartTime << " and ended at "
	     << X -> EndTime << "\n";

	cout << "Total CPU time: " << X ->CPUtotal << " in ";

	if(X -> CPUcount != 1){
		cout << X -> CPUcount << " CPU bursts.\n";
	}
	else{
		cout << "1 CPU burst.\n";
	}

	cout << "Total IO time: " << X -> IOtotal << " in ";

	if(X -> IOcount != 1){
		cout << X-> IOcount << " IO bursts.\n";
	}
	else{
		cout << "1 IO burst.\n";
	}

	//Get wait time
	Wait = X->EndTime - X->StartTime - X->CPUtotal - X->IOtotal;

	if(Wait > 0){
		cout << "Time waiting: " << Wait << "\n";
	}
	else{
		cout << "Time waiting: 0\n";
	}
	cout << "\n";

	delete X;		//Delete the current process
	NumInUse--;		//One less living process
	DeathCount++;		//He's in a better place
}


//I think this is the first program to make me have to clean slate it more than twice.
//This one was really confusing. We weren't given much to go on.
