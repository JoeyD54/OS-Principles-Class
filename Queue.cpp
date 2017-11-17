#include <iostream>
#include "Process.h"
#include "Queue.h"

using namespace std;

//Queue.cpp initializes all the variables to 0 and builds the functions

Queue::Queue()
{
	top = 0;
	bot = 0;
	qsize = 0;

	for(int i = 0; i < 5; i++){
		q[i] = 0;
	}
}


/*******************************************************************************************/



/*

Function: IsEmpty

This function checks if the count is equal to 0. If it is return 1, otherwise return 0

Args: N/A

*/

bool Queue::IsEmpty() const		//Check for empty queue
{
	return (qsize == 0);
}

/*

Function: IsFull

This function checks if the count is equal to the max size of the queue. If it is return 1, otherwise return 0

Args: N/A

*/

//bool Queue::IsFull()			//Check for full queue
//{
//	return (qsize == QUEUE_SIZE);
//}


/*

Function: push

This function will cause a process to move onto a given queue

Args: Process pointer

*/

void Queue::push(InUse * & A)
{
	q[bot] = A;				//Put new process into bottom of queue
	qsize++;				//Increment size count
	if(bot < 5 - 1){			//Check if near full. If not, increment size
		bot++;
	}
	else{					//If full, reset bot to 0
		bot = 0;
	}
}


/*

Function: pop

This function will cause a process to move off a given queue

Args: N/A

*/

InUse * Queue::pop()
{
	InUse* A;				//Declare Process variable
	A = q[top];				//Set it to top of queue
	q[top] = 0;				//Set location to 0
	qsize--;				//Decrement size count
	if(top < 5 - 1){			//Check if top is 1 below max size
		top++;				//Increment if less than queue max
	}
	else{					//If full, reset to 0
		top = 0;
	}
	return A;				//Return process variable
}



/*

Function: PrintQueue

This function will print the contents of any queue

Args: N/A

*/
/*
void Queue::PrintQ()
{
	if(qsize != 0){					//Check for non empty queue
		int i;
		for(i = 0; i < 5; i++){			//go through queue
			if(q[i] > 0){			//so long as the queue is not empty, print it's contents
				cout << "Queue[" << i << "] = " << q[i]->ProcessID << "\n";
			}
		}
	}
	else{
		cout << "Empty\n";
	}
}
*/
