#include <string.h>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

using namespace std;

/*

Program: 3
Programmer: Joey Domino

Due Date: 9/25/15 11:59 pm

This program creates runs 2 processes with pipes communicating between eachother through pipes. The processes
will read a number through a pipe, convert it to an integer, do math, convert the result into a string, and
send that string back to the other process via another pipe.

*/

void PWork(int[2], int[2]);				//initialize the two functions
void CWork(int[2], int[2]);


int main()
{
	int PipeA[2];					//Create and pipe the 2 pipe variables
	int PipeB[2];
	int ReturnA = pipe(PipeA);
	int ReturnB = pipe(PipeB);

	if(ReturnA == -1){				//Check for failure for either pipe
		cout << "Pipe A faield.\n";
		exit(-5);
	}
	if(ReturnB == -1){
		cout << "Pipe B failed.\n";
		exit(-5);
	}

	int ForkReturn = fork();			//Fork and check for failure
	if(ForkReturn == -1){
		cout << "Fork failed.\n";
		exit(-5);
	}

	//parent check
	if(ForkReturn > 0){
		close(PipeA[0]);			//Close read end of PipeA
		close(PipeB[1]);			//Close write end of PipeB

		PWork(PipeA, PipeB);			//Call function PWork

		close(PipeA[1]);			//Close write end of PipeA
		close(PipeB[0]);			//Close read end of PipeB

		wait(0);				//Wait for child process to exit with 0

		return 0;				//End parent process. return 0 to main
	}

	//child check
	if(ForkReturn == 0){
		close(PipeA[1]);			//Close write end of PipeA
		close(PipeB[0]);			//Close read end of PipeB

		CWork(PipeA, PipeB);			//Call function CWork

		close(PipeA[0]);			//Close read end of PipeA
		close(PipeB[1]);			//Close write end of PipeB

		exit(0);				//Close child process to return to parent process
	}

	return 0;
}




/*******************************************

Function: PWork(int[2], int[2])

This function takes in 2 pipes. It writes to one and reads from the other. The written pipe is delivered to
the child process. The pipe read from is coming from the child process.

return:

*********************************************/

void PWork(int PipeA[2], int PipeB[2])
{
	char Buffer[10];						//Declare buffer size
	char Value[10] = "1";						//Declare value
	int M = 0;							//Declare M

	write(PipeA[1], Value, 10);					//Write initial value to the child process

	cout << "Parent: Value = " << atoi(Value) << "\n";		//Print first statement

	while(strlen(Value) < 8){					//While value is 8 or less spaces long
		read(PipeB[0], Value, 10);				//Read from child pipe until EOF
		M = atoi(Value);					//Set M to the value of Value
		M = 3 * M + 1;						//Do given calculation
		sprintf(Buffer, "%d", M);				//Conver M to a string, put in Buffer
		write(PipeA[1], Buffer,(strlen(Buffer)+1));		//Send value to child process
		cout << "Parent: Value = " << M << "\n"; 		//Print current value

	}
}


/*******************************************

Function: CWork(int[2], int[2])

This function takes in 2 pipes. One writes to the parent process while the other reads from the parent.
These continue until the size of value is 8

Return:

*********************************************/

void CWork(int PipeA[2], int PipeB[2])
{
	char Buffer[10];						//Declare buffer size
	char Value[10];							//Declare Value
	int M = 0;							//Declare M

	while(strlen(Value) < 8){					//While value is 8 or less spaces long
			read(PipeA[0], Value, 10);			//Read from parent pipe until EOF
			M = atoi(Value);				//Set M to the value of Value
			M = 3 * M + 1;					//Do given calculation
			sprintf(Buffer, "%d", M);			//Conver M to a string, put in Buffer
			write(PipeB[1], Buffer,(strlen(Buffer)+1));	//Send value to parent process
			cout << "Child:  Value = " << M << "\n";	//Print current value
	}
}
