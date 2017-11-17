#include "Process.h"

//Initialize the 2 linked lists to 0
/*
Process::Process()
{
	Command = "";				//Initialize all to 0
	ProcessID = 0;
	Size = 0;
	BlockID = "";
}
*/


InUse::InUse()
{
	Address = 0;				//Set address to 0
	Size = 0;				//Set size to 0

}



Avail::Avail()
{
	OneMBAdd = 3145728;			//Set first address to 3145728 (3 MB in)
	OneMB = ONEMB;				//Set 1 MB to one MB

	FirstTwoAdd = OneMBAdd + ONEMB;		//First 2 MB address is the first add plus one MB
	FirstTwo = TWOMB;

	SecondTwoAdd = FirstTwoAdd + TWOMB;	//Second 2 MB address is the first 2nd address plus 2 MB
	SecondTwo = TWOMB;

	FirstFourAdd = SecondTwoAdd + TWOMB;	//First 4 MB address is the 2nd 2 MB address plus 2 MB
	FirstFour = FOURMB;

	SecondFourAdd = FirstFourAdd + FOURMB;	//Sedond 4 MB address is the first 4 MB address plus 4 MB
	SecondFour = FOURMB;

}

