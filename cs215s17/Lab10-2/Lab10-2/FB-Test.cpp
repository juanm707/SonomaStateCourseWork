
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
rlimit __trl4 = {1000, __trl3.rlim_max};
const int __trl4r = setrlimit(RLIMIT_FSIZE, & __trl4);
// End of time limit code

#include <iostream>
#include "LList.hpp"

int main ()
{
	LList<int> LL;
	for (int i = 0; i < 10; i++)
		if (i % 2)
			LL.InsertFirst (i);
		else
			LL.InsertLast (i);
	cout << "The list (first to last): " << '[' << LL << ']' << endl;
	LL.SetDirection (BACKWARD);
	cout << "The list (last to first): " << '[' << LL << ']' << endl;
	return 0;
}
