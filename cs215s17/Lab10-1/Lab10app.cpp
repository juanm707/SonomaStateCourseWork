// Lab 10 application program
// Author: Dr. Watts
// Data: Fall 2011
// Description: This program is designed to test the LList class.

// Beginning of time limit code
#include <sys/time.h>
#include <sys/resource.h>
#include <unistd.h>

int getrlimit(int resource, struct rlimit *rlim);
int getrusage(int who, struct rusage *usage);
int setrlimit(int resource, const struct rlimit *rlim);
rlimit __trl1;
const int __trl1r = getrlimit(RLIMIT_CPU, & __trl1);
rlimit __trl2 = {10, __trl1.rlim_max};
const int __trl2r = setrlimit(RLIMIT_CPU, & __trl2);
rlimit __trl3;
const int __trl3r = getrlimit(RLIMIT_FSIZE, & __trl3);
rlimit __trl4 = {10000, __trl3.rlim_max};
const int __trl4r = setrlimit(RLIMIT_FSIZE, & __trl4);
// End of time limit code


#include <iostream>
#include <fstream>
#include <cstdlib>
#include "LList.h"

using namespace std;

int main (int argc, char * argv[])
{
// Test for existence of file name argument
	if (argc < 2)
	{
		cerr << "Usage: " << argv[0] << " <file-name>\n";
		exit (1);
	}

// Test to see if file was opened
	ifstream ins (argv[1]);
	if (ins.fail ())
	{
		cerr << "No file " << argv[1] << " found\n";
		exit (2);
	}
	
	LList LL;
	char action;
	int value;

	while (ins >> action)
	    switch (action)
	    {
		case 'D' : if (LL.DeleteFirst ())
				cout << "First value deleted from list\n";
			   else
				cout << "First value not deleted from list\n";
			   break;
		case 'E' : if (LL.DeleteLast ())
				cout << "Last value deleted from list\n";
			   else
				cout << "Last value not deleted from list\n";
			   break;
		case 'I' : ins >> value;
			   if (LL.InsertFirst (value))
				cout << value << " inserted at front of list\n";
			   else
				cout << value << " not inserted at front of list\n";
			   break;
		case 'J' : ins >> value;
			   if (LL.InsertLast (value))
				cout << value << " inserted at end of list\n";
			   else
				cout << value << " not inserted at end of list\n";
			   break;
		case 'S' : cout << "Size of list: " << LL.Size() << endl;
			   break;
		case 'W' : cout << "List: [" << LL << "]" << endl;
			   break;
		case 'C' : 
			{
				LList L1 = LL;
				LList L2 = LL;
				L1.InsertFirst(15);  
				L2.InsertLast(55);  
				LList L3;
				L3 = L2;
				if (L2 == L3)
					cout << "L2 is the same as L3\n";
				else
					cout << "L2 is NOT the same as L3\n";
				L3.InsertLast(100);
				if (L2 == L3)
					cout << "L2 is the same as L3\n";
				else
					cout << "L2 is NOT the same as L3\n";
				cout << "L1 = [" << L1 << "]\n";
				cout << "L2 = [" << L2 << "]\n";
				cout << "L3 = [" << L3 << "]\n";
			}
			break;
		case 'X' :
			exit (3);
		default :  cout << action << " is not a valid option\n";
	    }
	return 0;
}

