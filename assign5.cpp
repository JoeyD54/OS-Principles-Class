#include "Constants.h"
#include "Process.h"
#include "Queue.h"
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <sstream>


using namespace std;

/*

Joey Domino


This program will simulate memory management. The user will signify whether to use the best or first fit
algorithm to sort the incoming data.


*/

void First(string, int, int, string, Avail *, InUse *);
void Best(string, int, int, string, Avail *, InUse *);
void Print(Avail *, InUse *);

int count = 5;				//count for printing in each type of loop


Avail * A;				//Initialize the Available blocks
//Process * P;				//Initialize the process blocks
InUse * Use;				//Initialize the in use blocks

int main()
{
	string choice;			//String to clarify what the user wants
	A = new Avail;			//set new available variable
	Use = new InUse;		//Set new in use stack

	string Command = "";
	int ProcessID = 0;
	int Size = 0;
	string BlockID = "";


	cout << "\nWelcome to the memory allocation program!\n"
	     << "Which sorting algorithm would you like to use? (F) for first-fit, (B) for best-fit: ";

	cin >> choice;			//Set decision

//	cout << "Total size = " << A->OneMB + A->FirstTwo + A->SecondTwo + A->FirstFour = A->SecondFour << "\n\n";

	//Now print the  current in use blocks

//	cout << "List of blocks in use: \n";
//	if(


	if(choice == "f" || choice == "F"){
		cout << "Simulating a First-Fit Memory Management Algorithm\n\n";
		cout << "Beginning simulation\n";
	}
	else if(choice == "b" || choice == "B"){
		cout << "Simulating a Best-Fit Memory Management Algorithm\n\n";
		cout << "Beginning simulation\n";
	}

	string line = "";

	ifstream MyFile("data5.txt");
	if(MyFile.is_open()){
		while(getline(MyFile, line)){
			stringstream ss(line);
			ss >> Command;
			if(Command != "?"){
				//ss >> Command;
				ss >> ProcessID;
				ss >> Size;
				ss >> BlockID;

				//Seperate the line into the 4 variables if they are there


				//cout << Command << ProcessID << Size << BlockID << "\n";


				if(choice == "f" || choice == "F"){
					First(Command, ProcessID, Size, BlockID, A, Use);
				}
				else if(choice == "b" || choice == "B"){
					Best(Command, ProcessID, Size, BlockID, A, Use);
				}
				else{
					cout << "That isn't a valid choice! Restart.\n";
					break;
				}

			}
		}
	}

	MyFile.close();					//close file

	cout << "\n\n-------------------------------------------\n";
	cout << "End of run\n";
	Print(A,Use);

}
/*

Function: First

Use: This function will simulate a first fit algorithm for memory management.

return:

*/

void First(string Command, int ProcessID, int Size, string BlockID, Avail * A, InUse * Use)
{
	if(count == HOW_OFTEN){
		Print(A,Use);				//Print contents and reset for run
		count = 0;
	}

	//Go through all 4 possible command choices
	if(Command == "L"){
		cout << "Received request to load process " << ProcessID << ", block ID "
		     << BlockID << " using " << Size << " bytes\n";


		if(A->OneMB < Size && A->FirstTwo < Size && A->SecondTwo < Size && A->FirstFour < Size && A->SecondFour < Size){
			cout << "No block big enough for file\n";
		}
		if(A -> OneMB > Size){
			cout << "Found block of size " << A->OneMB << "\n";

			Use -> Address = A -> OneMBAdd; //Set new address
			Use -> Size = Size;		//Set use size
			A -> OneMBAdd = A->OneMBAdd + Size;
			A -> OneMB -= Size;

			cout << Use -> Address << " " << Use -> Size << "\n";
			cout << A -> OneMBAdd << " "  << A -> OneMB << "\n";

		}

		count++;
	}

	if(Command == "T"){
		cout << "Received request to terminate process " << ProcessID << "\n";

		

		count++;
	}

	if(Command == "A"){
		cout << "Received request to allocate " << Size << " bytes for process " << ProcessID
		     << ", block ID " << BlockID << "\n";


		count++;
	}

	if(Command == "D"){
		cout << "Received request to deallocate block ID " << BlockID << " for process "
		     << ProcessID << "\n";

		count++;
	}

}

/*

Function: Best

Use: This function simulates a best fit algorithm for memory management

Return:

*/

void Best(string Command, int ProcessID, int Size, string BlockID, Avail * A, InUse * Use)
{
	if(count == HOW_OFTEN){					//Print and reset counter for run
		Print(A,Use);
		count = 0;
	}

//	int BestFit;

//	bool foundBest = false;



//	while(!foundBest){
//		if(A->

	//Go through all 4 possible command choices
	if(Command == "L"){
		cout << "Received request to load process " << ProcessID << ", block ID "
		     << BlockID << " using " << Size << " bytes\n";

		count++;
	}

	if(Command == "T"){
		cout << "Received request to terminate process " << ProcessID << "\n";

		count++;
	}

	if(Command == "A"){
		cout << "Received request to allocate " << Size << " bytes for process " << ProcessID
		     << ", block ID " << BlockID << "\n";


		count++;
	}

	if(Command == "D"){
		cout << "Received request to deallocate block ID " << BlockID << " for process "
		     << ProcessID << "\n";


		count++;
	}

}


/*

Function: Print

Use: Thise function will pritn the available and in use blocks

Return:

*/


void  Print(Avail * A, InUse * Use)
{
	//Print the available blocks and in use blocks
	cout << "\nAvailable Block:\n";

	cout << "Start Address =  " << A -> OneMBAdd
	     << " Size = " << A -> OneMB << "\n";

	cout << "Start Address =  " << A -> FirstTwoAdd
	     << " Size = " << A -> FirstTwo << "\n";

	cout << "Start Address =  " << A -> SecondTwoAdd
	     << " Size = " << A -> SecondTwo << "\n";

	cout << "Start Address =  " << A -> FirstFourAdd
	     << " Size = " << A -> FirstFour << "\n";

	cout << "Start Address = " << A -> SecondFourAdd
	     << " Size = " << A -> SecondFour << "\n";

	int Total = A -> OneMB;
	Total += A -> FirstTwo;
	Total += A -> SecondTwo;
	Total += A -> FirstFour;
	Total += A -> SecondFour;

	cout << "Total size = " << Total << "\n\n";

	//Now print the  current in use blocks

	cout << "List of blocks in use: \n";
	if(Use -> Address == 0){
		cout << "NONE\nTotal size: 0\n\n";
	}
//	else{

}
