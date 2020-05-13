#include <iostream>
#include <ctime>
#include <cstdlib>
#include "LList2.hpp"

using namespace std;

int main ()
{
	LList2<int> L;
	srand (time (NULL));
	int num = rand() % 20 + 5;
	cout << "The value of num is " << num << endl;
	int val = rand() % 10;
	cout << "The value of val is " << val << endl;
	for (int n = 0; n < num; n++)
	{
		L.InsertFirst (val);
		val = (val * 17 - 13) % 100;
	}
	cout << L << endl;
	cout << "From first to last:\n";
	for (LList2<int>::Iterator itr = L.begin (); itr != L.end(); itr++)
		cout << "List value is " << * itr << endl;
	cout << "From last to first:\n";
	for (LList2<int>::Iterator itr = L.rbegin (); itr != L.rend(); itr--)
		cout << "List value is " << * itr << endl;
	cout << L << endl;
	return 0;
}
