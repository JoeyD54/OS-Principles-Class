//The queue header file creates all variables function prototypes for later use.

#ifndef QUEUE_H
#define QUEUE_H

#include "Process.h"

using namespace std;

class Queue
{
public:
	InUse * q[5];			//The array will never grow past 5

	//Initialize values to be used in functions in the functions below
	int qsize;
	int top;
	int bot;

	Queue();			//Constructor for the class


	//Create prototypes
	bool IsEmpty() const;
	void push(InUse * & A);
	InUse * pop();
	void PrintQ();
};

#endif
