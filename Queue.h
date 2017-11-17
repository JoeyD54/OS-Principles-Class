//The queue header file creates all variables function prototypes for later use.

#ifndef QUEUE_H
#define QUEUE_H

#include "Process.h"

using namespace std;

class Queue
{
public:
	Process * q[QUEUE_SIZE];
	//Initialize values to be used in functions in the functions below
	int qsize;
	int top;
	int bot;

	Queue();			//Constructor for the class
	//Create prototypes
	bool IsEmpty() const;
//	bool IsFull();
	void push(Process * & A);
	Process * pop();
	void PrintQ();
};

#endif
