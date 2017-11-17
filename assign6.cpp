#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <algorithm>

using namespace std;

/*
Programmer: Joey Domino


This program will take a given file and sort the values in it in a first in first out or least recently
used format. This will be decided by the given letter received from the file on every other line.

*/

void PrintFrames(int, int*, int, int, int, int, bool);

int main()
{
	//Create needed variables
	string Command;				//Command given
	int FrameNum;				//Number of frames
	int PageNum;				//Number of pages
	int list[20] = {0};			//File allows up to 20 steps
	bool Fault = 0;				//Bool to check for faults.
	bool IsEqual = 0;			//Equality check
	int StepCount = 0;			//Count for step print
	int FaultCount = 0;			//Count for total page faults
	int i = 0;				//Count for for loop
	int j = 0;				//Second count for loops



	//Create file name, open it, and sort data from it into variables and an array
	ifstream MyFile("data6.txt");
	string line;
	while(!MyFile.eof()){
		getline(MyFile,line);
		istringstream ss(line);

		ss >> Command;			//Store first value into command for algorithm check.
		ss >> PageNum;
		ss >> FrameNum;

		int Frame[FrameNum];		//Initialize the frame array size and fill it with -1's
		fill(Frame, Frame + sizeof(Frame), -1);

		int FrameTimer[FrameNum];	//Initialize timer for the LRU loop and set all to -3

		for(i = 0; i < FrameNum; i++){
			FrameTimer[i] = -13;
		}


		if(Command == "?"){		//end program on ?
			return 0;
		}

		getline(MyFile,line);		//Get next line for frames
		istringstream slist(line);

		for(i = 0; i <= 19; i++){	//Fill array
			slist >> list[i];
		}


		//Code for printing the seperator, title, and collumn labels

		for(i = 0; i < 60; i++){
			cout << "-";
		}
		cout << "\n\n";

		//print the title and the labels for the collumns
		if(Command == "F"){
			cout << "Simulating FIFO for " << PageNum << " Pages and " << FrameNum << " Frames.\n\n";
		}
		else if(Command == "L"){
			cout << "Simulating LRU for " << PageNum << " Pages and " << FrameNum << " Frames.\n\n";
		}
		else{
			return 0;			//End program if the command is not F or L
		}

		cout << setw(11) << "Next";

		for(i = 1; i <= FrameNum; i++){
			cout << setw(7) << "Frame";
		}

		cout << "\nStep" << setw(7) << "Page" << setw(5) << "0"; //Auto print the first frame num

		for(i = 1; i < FrameNum; i++){
			cout << setw(7) << i;
		}

		cout << setw(17) << "PageFault?" << "\n\n";

		//FIFO check and loop
		if(Command == "F"){

			//Code to Allocate the values in the array to the correct frame
			for(i = 0; i < 20; i++){			//While list array isn't used up
				if(j == FrameNum){
					j = 0;
				}
				if(list[i] != -1){			//Do these checks  while not -1
					if(count(Frame, Frame + FrameNum, list[i]) > 0){				//This finds if any number in the frame array holds any number of the current list number
						Fault = 0;
						PrintFrames(list[i], Frame, StepCount, FrameNum, PageNum, j, Fault);	//A bit too many variables, but I wanted to have my print seperated from my loops
						StepCount++;
						continue; 		//Skip the rest of the loop and start the next iteration
					}
					else{
						Fault = 1;
						FaultCount++;
						Frame[j] = list[i];	//Set frame to new value
						PrintFrames(list[i], Frame, StepCount, FrameNum, PageNum, j, Fault);
						StepCount++;
					}
				}
				else{
					break;				//End loop on -1
				}
			j++;						//Increment frame location
			}

		cout << "\nThere were " << FaultCount << " Faults in " << StepCount << " total steps.\n\n";

		StepCount = 0;		//Reset counters
		FaultCount = 0;
		j = 0;

		}

		//LRU check and loop
		if(Command == "L"){
			for(i = 0; i < 20; i++){
				if(list[i] != -1){
					if(j == FrameNum){
						j = 0;
					}
					for(int x = 0; x < FrameNum; x++){			//Go through every frame, if any are equal to the list number, print it and reset the timer
						if(Frame[x] == list[i]){
							Fault = 0;
							PrintFrames(list[i], Frame, StepCount, FrameNum, PageNum, j, Fault);
							FrameTimer[x] = -1;
							StepCount++;

							for(int k = 0; k < FrameNum; k++){	//Increment all timers
								FrameTimer[k]++;
							}

							IsEqual = 1;				//Set bool value for later check
							break;
						}
					}
					if(IsEqual == 1){
						IsEqual = 0;
						continue;
					}
					else if(Frame[j] == -1){				//Any frame with a timer of 0 gets replaced. Timer is then set to 1
						Fault = 1;
						FaultCount++;
						Frame[j] = list[i];				//Replace that Frame's number
						PrintFrames(list[i], Frame, StepCount, FrameNum, PageNum, j, Fault);
						FrameTimer[j] = -1;				//Set that frame's timer to 0.
						StepCount++;

						for(int k = 0; k < FrameNum; k++){		//Increment all timers
							FrameTimer[k]++;
						}
					}
					else{
						int temp = FrameTimer[j];			//Set current frame timer to a temp for comparisons
						for(int k = 0; k < FrameNum; k++){		//Find the frame with the highest timer
							if(FrameTimer[k] > temp){
								temp = FrameTimer[k];		//Set temp to new high FrameTime
								j = k;				//Set current frame to the highest frame location
							}
						}

						Fault = 1;
						FaultCount++;
						Frame[j] = list[i];				//Set frame number to the list number
						PrintFrames(list[i], Frame, StepCount, FrameNum, PageNum, j, Fault);
						FrameTimer[j] = -1;
						StepCount++;

						for(int x = 0; x < FrameNum; x++){
							FrameTimer[x]++;
						}
					}
				}
			j++;
			}

		cout << "\nThere were " << FaultCount << " Faults in " << StepCount << " total steps.\n\n";

		StepCount = 0;		//Reset counters
		FaultCount = 0;
		j = 0;

		}

	}

	MyFile.close();
	return 0;
}


void PrintFrames(int Page, int Frame[], int StepCount, int FrameNum, int PageNum, int FaultFrame, bool Fault)
{
	//Print the step number, page used, current contents of the frames, and if there was a fault

	cout << setw(4) << StepCount << setw(6) << Page << setw(6) << Frame[0];

	for(int i = 1; i <= FrameNum; i++){
		if(Frame[i] == -1){
			cout << setw(7) << " ";
		}
		else{
			cout << setw(7) << Frame[i];
		}
	}

	if(Fault == 1){
		cout << setw(12) << "Yes. In frame " << FaultFrame << endl;
	}
	else{
		cout << setw(3) << "No\n";
	}
}
