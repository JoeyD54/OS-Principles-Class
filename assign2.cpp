#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <iostream>
//#include <

using namespace std;

/*
Program 2

Programmer: Joey Domino
Due Date: 9/14/2015 11:59 PM

This program will cause a fork and print out the ID of the child and parent of each fork as well as the
	origional process

*/

int main()
{
	//origianl proces print
	cout << "This is the original process. My PID is " << getpid() << " and my parent's PID is "
	     << getppid() << ".\n";

	//fork process
	int Return = fork();

	//failure check
	if(Return == -1){
		cout << "Fork failed\n";
		return -1;
	}

	//parent check
	if(Return > 0){
		cout << "I am the parent process and my ID is " << getpid() << " and my parent's ID is "
		     << getppid() << ".\n";

		//call systems function
		cout << "I am the parent about to call ps.\n";

		//wait for child to end
		wait(0);
		system("ps");
		cout << "I am the parent process about to exit.\n";
	}

	//child check
	if(Return == 0){
		cout << "I am the child process and my ID is " << getpid() << " and my parent's ID is "
		     << getppid() << ".\n";

		//Do second fork
		int Return2 = fork();

		//Check for grandchild and then close it
		if(Return2 == 0){
			cout << "I am the grandchild. My ID is " << getpid() << " and my parent's ID is "
		     	     << getppid() << ".\n"
		     	     << "I am the grandchild about to exit.\n";
			return 0;
		}
	//wait for grandchild to close
	wait(0);
	//Close child process
	cout << "I am the child about to exit.\n";
	return 0;

}






}
